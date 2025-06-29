"""
Este script treina um perceptron multicamada (MLP) simples para aprender a função XOR usando a biblioteca scikit-learn.
O objetivo do código é demonstrar como uma rede neural com uma camada oculta de dois neurônios pode resolver o problema do XOR,
que não é linearmente separável. Ao final, o script imprime os pesos e bias aprendidos pela rede.
Funções principais:
- Define os dados de entrada e saída para o problema XOR.
- Treina um MLPClassifier com uma camada oculta de 2 neurônios e função de ativação 'tanh'.
- Exibe os pesos e bias das camadas treinadas.
"""

import numpy as np
from sklearn.neural_network import MLPClassifier

# Dados para XOR
X = np.array([[0,0],[0,1],[1,0],[1,1]])
y = np.array([0,1,1,0])

# Treina um MLP com camada oculta de 2 neurônios
clf = MLPClassifier(hidden_layer_sizes=(2,), activation='tanh', max_iter=10000)
clf.fit(X, y)

print("Pesos camada 1 (input -> hidden):")
print(clf.coefs_[0])
print("Bias camada 1:")
print(clf.intercepts_[0])
print("Pesos camada 2 (hidden -> output):")
print(clf.coefs_[1])
print("Bias camada 2:")
print(clf.intercepts_[1])