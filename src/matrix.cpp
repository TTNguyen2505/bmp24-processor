#include "../include/matrix.hpp"
#include <cmath>

static Matrix4x4 makeIdentity4x4() {
    Matrix4x4 m{};
    for (int i = 0; i < 4; ++i) {
        m.data[i][i] = 1.0;
    }
    return m;
}

static Matrix4x4 blendMatrix(const Matrix4x4 &identity, const Matrix4x4 &target, double amount) {
    Matrix4x4 result{};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.data[row][col] = (1.0 - amount) * identity.data[row][col] + amount * target.data[row][col];
        }
    }
    return result;
}

double determinant(const Matrix3x3 &matrix) {
    return matrix.data[0][0] * (matrix.data[1][1] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][1])
         - matrix.data[0][1] * (matrix.data[1][0] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][0])
         + matrix.data[0][2] * (matrix.data[1][0] * matrix.data[2][1] - matrix.data[1][1] * matrix.data[2][0]);
}

Matrix3x3 inverse(const Matrix3x3 &matrix) {
    double det = determinant(matrix);
    if (det == 0.0) {
        return {};
    }

    Matrix3x3 inv{};
    inv.data[0][0] =  (matrix.data[1][1] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][1]) / det;
    inv.data[0][1] = -(matrix.data[0][1] * matrix.data[2][2] - matrix.data[0][2] * matrix.data[2][1]) / det;
    inv.data[0][2] =  (matrix.data[0][1] * matrix.data[1][2] - matrix.data[0][2] * matrix.data[1][1]) / det;
    inv.data[1][0] = -(matrix.data[1][0] * matrix.data[2][2] - matrix.data[1][2] * matrix.data[2][0]) / det;
    inv.data[1][1] =  (matrix.data[0][0] * matrix.data[2][2] - matrix.data[0][2] * matrix.data[2][0]) / det;
    inv.data[1][2] = -(matrix.data[0][0] * matrix.data[1][2] - matrix.data[0][2] * matrix.data[1][0]) / det;
    inv.data[2][0] =  (matrix.data[1][0] * matrix.data[2][1] - matrix.data[1][1] * matrix.data[2][0]) / det;
    inv.data[2][1] = -(matrix.data[0][0] * matrix.data[2][1] - matrix.data[0][1] * matrix.data[2][0]) / det;
    inv.data[2][2] =  (matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1] * matrix.data[1][0]) / det;
    return inv;
}

Matrix3x3 operator*(const Matrix3x3 &lhs, const Matrix3x3 &rhs) {
    Matrix3x3 result{};
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            double sum = 0.0;
            for (int k = 0; k < 3; ++k) {
                sum += lhs.data[row][k] * rhs.data[k][col];
            }
            result.data[row][col] = sum;
        }
    }
    return result;
}

Matrix4x4 operator*(const Matrix4x4 &lhs, const Matrix4x4 &rhs) {
    Matrix4x4 result{};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            double sum = 0.0;
            for (int k = 0; k < 4; ++k) {
                sum += lhs.data[row][k] * rhs.data[k][col];
            }
            result.data[row][col] = sum;
        }
    }
    return result;
}

Vector4 operator*(const Matrix4x4 &lhs, const Vector4 &rhs) {
    Vector4 result{};
    result.x = lhs.data[0][0] * rhs.x + lhs.data[0][1] * rhs.y + lhs.data[0][2] * rhs.z + lhs.data[0][3] * rhs.w;
    result.y = lhs.data[1][0] * rhs.x + lhs.data[1][1] * rhs.y + lhs.data[1][2] * rhs.z + lhs.data[1][3] * rhs.w;
    result.z = lhs.data[2][0] * rhs.x + lhs.data[2][1] * rhs.y + lhs.data[2][2] * rhs.z + lhs.data[2][3] * rhs.w;
    result.w = lhs.data[3][0] * rhs.x + lhs.data[3][1] * rhs.y + lhs.data[3][2] * rhs.z + lhs.data[3][3] * rhs.w;
    return result;
}

Matrix3x3 createTranslationMatrix(double tx, double ty) {
    Matrix3x3 mat{};
    mat.data[0][0] = 1.0;
    mat.data[1][1] = 1.0;
    mat.data[2][2] = 1.0;
    mat.data[0][2] = tx;
    mat.data[1][2] = ty;
    return mat;
}

Matrix3x3 createScaleMatrix(double sx, double sy) {
    Matrix3x3 mat{};
    mat.data[0][0] = sx;
    mat.data[1][1] = sy;
    mat.data[2][2] = 1.0;
    return mat;
}

Matrix3x3 createRotationMatrix(double theta) {
    Matrix3x3 mat{};
    double c = std::cos(theta);
    double s = std::sin(theta);
    mat.data[0][0] =  c;
    mat.data[0][1] = -s;
    mat.data[1][0] =  s;
    mat.data[1][1] =  c;
    mat.data[2][2] = 1.0;
    return mat;
}

Matrix3x3 createShearMatrix(double alpha, double beta) {
    Matrix3x3 mat{};
    mat.data[0][0] = 1.0;
    mat.data[0][1] = alpha;
    mat.data[1][0] = beta;
    mat.data[1][1] = 1.0;
    mat.data[2][2] = 1.0;
    return mat;
}

Matrix4x4 createGrayscaleMatrix(double amount) {
    Matrix4x4 identity = makeIdentity4x4();
    Matrix4x4 gray{};
    const double r = 0.2126;
    const double g = 0.7152;
    const double b = 0.0722;

    gray.data[0][0] = r;
    gray.data[0][1] = g;
    gray.data[0][2] = b;
    gray.data[1][0] = r;
    gray.data[1][1] = g;
    gray.data[1][2] = b;
    gray.data[2][0] = r;
    gray.data[2][1] = g;
    gray.data[2][2] = b;
    gray.data[3][3] = 1.0;

    return blendMatrix(identity, gray, amount);
}

Matrix4x4 createSepiaMatrix(double amount) {
    Matrix4x4 identity = makeIdentity4x4();
    Matrix4x4 sepia{};
    sepia.data[0][0] = 0.393;
    sepia.data[0][1] = 0.769;
    sepia.data[0][2] = 0.189;
    sepia.data[1][0] = 0.349;
    sepia.data[1][1] = 0.686;
    sepia.data[1][2] = 0.168;
    sepia.data[2][0] = 0.272;
    sepia.data[2][1] = 0.534;
    sepia.data[2][2] = 0.131;
    sepia.data[3][3] = 1.0;

    return blendMatrix(identity, sepia, amount);
}

Matrix4x4 createInvertMatrix(double amount) {
    Matrix4x4 identity = makeIdentity4x4();
    Matrix4x4 invert{};
    invert.data[0][0] = -1.0;
    invert.data[1][1] = -1.0;
    invert.data[2][2] = -1.0;
    invert.data[0][3] = 1.0;
    invert.data[1][3] = 1.0;
    invert.data[2][3] = 1.0;
    invert.data[3][3] = 1.0;

    return blendMatrix(identity, invert, amount);
}

Matrix4x4 createBrightnessMatrix(double amount) {
    Matrix4x4 mat = makeIdentity4x4();
    mat.data[0][0] = amount;
    mat.data[1][1] = amount;
    mat.data[2][2] = amount;
    return mat;
}

Matrix4x4 createContrastMatrix(double amount) {
    Matrix4x4 mat{};
    mat.data[0][0] = amount;
    mat.data[1][1] = amount;
    mat.data[2][2] = amount;
    mat.data[0][3] = 0.5 * (1.0 - amount);
    mat.data[1][3] = 0.5 * (1.0 - amount);
    mat.data[2][3] = 0.5 * (1.0 - amount);
    mat.data[3][3] = 1.0;
    return mat;
}

Matrix4x4 createSaturateMatrix(double amount) {
    const double r = 0.2126;
    const double g = 0.7152;
    const double b = 0.0722;
    double oneMinus = 1.0 - amount;

    Matrix4x4 mat{};
    mat.data[0][0] = oneMinus * r + amount;
    mat.data[0][1] = oneMinus * g;
    mat.data[0][2] = oneMinus * b;
    mat.data[1][0] = oneMinus * r;
    mat.data[1][1] = oneMinus * g + amount;
    mat.data[1][2] = oneMinus * b;
    mat.data[2][0] = oneMinus * r;
    mat.data[2][1] = oneMinus * g;
    mat.data[2][2] = oneMinus * b + amount;
    mat.data[3][3] = 1.0;
    return mat;
}
