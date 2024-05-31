import numpy as np
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
digits = load_digits()
X_train, X_test, y_train, y_test = train_test_split(digits.data, digits.target)
tree = DecisionTreeClassifier()
tree.fit(X_train, y_train)
y_pred = tree.predict(X_test)
print(np.sum(y_test == y_pred))
print(np.average(y_test == y_pred))
