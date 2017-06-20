# mnist-data

## 概要
mnist 手書き文字データを PNG 形式で出力.

### 使用方法
``./mnist-data``  
mnist-data と同じ場所に下記(任意に設定可能)のファイルが存在する状態で実行.
```c:include/mnist.h
#define MNIST_LABEL_PATH "train-labels-idx1-ubyte" // ラベルファイルパス
#define MNIST_IMAGE_PATH "train-images-idx3-ubyte" // イメージファイルパス
```
