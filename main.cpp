#include <iostream>
using namespace std;

// -------------------------------------------------------------
// Clase base abstracta
// Define el comportamiento que deben tener todas las matrices.
// -------------------------------------------------------------
template <typename T>
class MatrizBase {
protected:
    int filas, columnas; 

public:
    MatrizBase(int f, int c) : filas(f), columnas(c) {}
    virtual void cargarValores() = 0;
    // Método obligatorio para mostrar los datos
    virtual void imprimir() const = 0;
    // Método obligatorio para sumar matrices
    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otra) const = 0;
    // Destructor virtual para evitar errores al eliminar objetos derivados
    virtual ~MatrizBase() {}
};
// -------------------------------------------------------------
// Clase Matriz Dinámica
// Usa memoria dinámica, se puede crear del tamaño que queramos.
// -------------------------------------------------------------
template <typename T>
class MatrizDinamica : public MatrizBase<T> {
    T** datos; // puntero doble para manejar la matriz
public:
    // Constructor: reserva memoria
    MatrizDinamica(int f, int c) : MatrizBase<T>(f, c) {
        datos = new T*[f];
        for (int i = 0; i < f; i++)
            datos[i] = new T[c];
    }
    // Destructor: libera memoria
    ~MatrizDinamica() {
        for (int i = 0; i < this->filas; i++)
            delete[] datos[i];
        delete[] datos;
    }
    // Cargar valores desde teclado
    void cargarValores() override {
        cout << "Ingrese los valores de la matriz (" << this->filas << "x" << this->columnas << "):\n";
        for (int i = 0; i < this->filas; i++) {
            for (int j = 0; j < this->columnas; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> datos[i][j];
            }
        }
    }
    // Mostrar matriz en consola
    void imprimir() const override {
        for (int i = 0; i < this->filas; i++) {
            for (int j = 0; j < this->columnas; j++) {
                cout << "| " << datos[i][j] << " ";
            }
            cout << "|\n";
        }
    }
    // Sumar matrices dinámicas
    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        const MatrizDinamica<T>& B = dynamic_cast<const MatrizDinamica<T>&>(otra);
        // Creamos una nueva matriz resultado
        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(this->filas, this->columnas);
        // Sumamos elemento por elemento
        for (int i = 0; i < this->filas; i++) {
            for (int j = 0; j < this->columnas; j++) {
                resultado->datos[i][j] = this->datos[i][j] + B.datos[i][j];
            }
        }

        return resultado;
    }
};

// -------------------------------------------------------------
// Clase Matriz Estática
// Su tamaño es fijo y no usa memoria dinámica.
// -------------------------------------------------------------
template <typename T, int M, int N>
class MatrizEstatica : public MatrizBase<T> {
    T datos[M][N]; // matriz fija

public:
    MatrizEstatica() : MatrizBase<T>(M, N) {}

    void cargarValores() override {
        cout << "Ingrese los valores de la matriz estatica (" << M << "x" << N << "):\n";
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << "Elemento [" << i << "][" << j << "]: ";
                cin >> datos[i][j];
            }
        }
    }

    void imprimir() const override {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << "| " << datos[i][j] << " ";
            }
            cout << "|\n";
        }
    }

    MatrizBase<T>* sumar(const MatrizBase<T>& otra) const override {
        const MatrizEstatica<T, M, N>& B = dynamic_cast<const MatrizEstatica<T, M, N>&>(otra);
        MatrizEstatica<T, M, N>* resultado = new MatrizEstatica<T, M, N>();

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                resultado->datos[i][j] = this->datos[i][j] + B.datos[i][j];
            }
        }

        return resultado;
    }
};
// -------------------------------------------------------------
// Función principal (main)
// Aquí probamos todo el sistema con ejemplos simples.
// -------------------------------------------------------------
int main() {
    cout << "--- Sistema Genérico de Álgebra Lineal ---\n";
    // Creamos dos matrices dinámicas tipo float
    MatrizBase<float>* A = new MatrizDinamica<float>(2, 2);
    MatrizBase<float>* B = new MatrizDinamica<float>(2, 2);

    cout << "\nMatriz A:\n";
    A->cargarValores();

    cout << "\nMatriz B:\n";
    B->cargarValores();

    // Sumamos matrices
    cout << "\n>> Sumando matrices...\n";
    MatrizBase<float>* C = A->sumar(*B);

    cout << "\nResultado (A + B):\n";
    C->imprimir();

    // Liberamos memoria
    delete A;
    delete B;
    delete C;

    cout << "\nMemoria liberada correctamente.\n";
    cout << "Programa finalizado con exito.\n";
    return 0;
}
