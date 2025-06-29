#include <math.h>
#define UART_BASE 0xe0001800

// PESOS EXPORTADOS DO SEU MODELO PYTHON
float weights_input_hidden[2][2] = {
    { -2.15923056,  2.40396106 },  // X0 para hidden1 e hidden2
    { -2.18442468,  2.58112841 }   // X1 para hidden1 e hidden2
};
float bias_hidden[2] = {  3.13329258, -1.07970179 };
float weights_hidden_output[2] = { 2.67689145, 2.84617304 };
float bias_output = -2.28319713;

// Função tanh (usa math.h)
float my_tanh(float x) {
    if(x < -20) return -1.0;
    if(x > 20) return 1.0;
    float ex = expf(x);
    float enx = expf(-x);
    return (ex - enx) / (ex + enx);
}

// Função sigmóide
float my_sigmoid(float x) {
    if(x < -20) return 0.0;
    if(x > 20) return 1.0;
    return 1.0 / (1.0 + expf(-x));
}

static void uart_write(char c) {
    volatile unsigned int *uart_txfull = (unsigned int *)(UART_BASE + 0x18);
    volatile unsigned int *uart_rxtx   = (unsigned int *)(UART_BASE + 0x00);
    while (*uart_txfull);
    *uart_rxtx = c;
}

static void uart_print(const char *s) {
    while (*s)
        uart_write(*s++);
}

// Imprime float formatado
void uart_print_dec(float v) {
    int vi = (int)(v * 1000);
    int int_part = vi / 1000;
    int frac_part = vi < 0 ? -(vi % 1000) : (vi % 1000);
    char buf[32];
    int n = 0;
    if (vi < 0) { buf[n++] = '-'; }
    int_part = int_part < 0 ? -int_part : int_part;
    // Só 1 dígito da parte inteira porque só vai dar 0 ou 1
    buf[n++] = '0' + (int_part % 10);
    buf[n++] = '.';
    buf[n++] = '0' + ((frac_part / 100) % 10);
    buf[n++] = '0' + ((frac_part / 10) % 10);
    buf[n++] = '0' + (frac_part % 10);
    buf[n] = 0;
    uart_print(buf);
}

// Inferência (XOR)
float mlp_infer(float x0, float x1) {
    float h[2];
    for (int i = 0; i < 2; i++) {
        h[i] = bias_hidden[i] + weights_input_hidden[0][i] * x0 + weights_input_hidden[1][i] * x1;
        h[i] = my_tanh(h[i]);
    }
    float out = bias_output + weights_hidden_output[0]*h[0] + weights_hidden_output[1]*h[1];
    out = my_sigmoid(out);
    return out;
}

// Função principal
void _start() {
    uart_print("MLP XOR Inference:\n");
    for(int a=0;a<=1;a++)
        for(int b=0;b<=1;b++) {
            float r = mlp_infer((float)a, (float)b);
            uart_print("Input: ");
            uart_write('0'+a);
            uart_write(' ');
            uart_write('0'+b);
            uart_print(" => Output: ");
            uart_print_dec(r);
            uart_print("\n");
        }
    __asm__ volatile ("ebreak");
}