#pragma once

/**
 * @struct Matrix3x3
 * @brief Represents a 3×3 matrix for geometric transformations.
 */
struct Matrix3x3 {
    double data[3][3]{{0.0}};
};

/**
 * @struct Matrix4x4
 * @brief Represents a 4×4 matrix for color transformations.
 */
struct Matrix4x4 {
    double data[4][4]{{0.0}};
};

/**
 * @struct Vector4
 * @brief Defines a 4D color vector used for homogeneous color operations.
 */
struct Vector4 {
    double x{0.0}; /**< X component, typically red. */
    double y{0.0}; /**< Y component, typically green. */
    double z{0.0}; /**< Z component, typically blue. */
    double w{0.0}; /**< W component, typically alpha or homogeneous coordinate. */
};

/**
 * @brief Computes the determinant of a 3×3 matrix.
 * @param matrix Input matrix.
 * @return The determinant value.
 */
[[nodiscard]]
double determinant(const Matrix3x3 &matrix);

/**
 * @brief Computes the inverse of a 3×3 matrix.
 * @param matrix Input matrix.
 * @return The inverse matrix.
 */
[[nodiscard]]
Matrix3x3 inverse(const Matrix3x3 &matrix);

/**
 * @brief Multiplies two 3×3 matrices.
 * @param lhs Left-hand matrix.
 * @param rhs Right-hand matrix.
 * @return The resulting matrix.
 */
[[nodiscard]]
Matrix3x3 operator*(const Matrix3x3 &lhs, const Matrix3x3 &rhs);

/**
 * @brief Multiplies two 4×4 matrices.
 * @param lhs Left-hand matrix.
 * @param rhs Right-hand matrix.
 * @return The resulting matrix.
 */
[[nodiscard]]
Matrix4x4 operator*(const Matrix4x4 &lhs, const Matrix4x4 &rhs);

/**
 * @brief Transforms a 4D vector by a 4×4 matrix.
 * @param lhs Color transformation matrix.
 * @param rhs 4D vector representing RGB and homogeneous coordinate.
 * @return Transformed 4D vector.
 */
[[nodiscard]]
Vector4 operator*(const Matrix4x4 &lhs, const Vector4 &rhs);

/**
 * @brief Creates a translation matrix.
 * @param tx Translation along the x-axis.
 * @param ty Translation along the y-axis.
 * @return A translation matrix.
 */
[[nodiscard]]
Matrix3x3 createTranslationMatrix(double tx, double ty);

/**
 * @brief Creates a scaling matrix.
 * @param sx Scale factor along the x-axis.
 * @param sy Scale factor along the y-axis.
 * @return A scaling matrix.
 */
[[nodiscard]]
Matrix3x3 createScaleMatrix(double sx, double sy);

/**
 * @brief Creates a rotation matrix.
 * @param theta Rotation angle in radians.
 * @return A rotation matrix.
 */
[[nodiscard]]
Matrix3x3 createRotationMatrix(double theta);

/**
 * @brief Creates a shear matrix.
 * @param alpha Shear angle along the x-axis.
 * @param beta Shear angle along the y-axis.
 * @return A shear matrix.
 */
[[nodiscard]]
Matrix3x3 createShearMatrix(double alpha, double beta);

/**
 * @brief Creates a grayscale filter matrix.
 * @param amount Grayscale intensity factor in the range [0.0, 1.0].
 * @return A grayscale filter matrix.
 */
[[nodiscard]]
Matrix4x4 createGrayscaleMatrix(double amount);

/**
 * @brief Creates a sepia filter matrix.
 * @param amount Sepia intensity factor in the range [0.0, 1.0].
 * @return A sepia filter matrix.
 */
[[nodiscard]]
Matrix4x4 createSepiaMatrix(double amount);

/**
 * @brief Creates a color inversion filter matrix.
 * @param amount Inversion intensity factor in the range [0.0, 1.0].
 * @return An inversion filter matrix.
 */
[[nodiscard]]
Matrix4x4 createInvertMatrix(double amount);

/**
 * @brief Creates a brightness adjustment matrix.
 * @param amount Brightness adjustment factor in the range [0.0, +∞).
 * @return A brightness adjustment matrix.
 */
[[nodiscard]]
Matrix4x4 createBrightnessMatrix(double amount);

/**
 * @brief Creates a contrast adjustment matrix.
 * @param amount Contrast adjustment factor in the range [0.0, +∞).
 * @return A contrast adjustment matrix.
 */
[[nodiscard]]
Matrix4x4 createContrastMatrix(double amount);

/**
 * @brief Creates a saturation adjustment matrix.
 * @param amount Saturation adjustment factor in the range [0.0, +∞).
 * @return A saturation adjustment matrix.
 */
[[nodiscard]]
Matrix4x4 createSaturateMatrix(double amount);
