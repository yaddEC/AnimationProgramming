#include "Maths.h"
using namespace Math;

//===== Change Radiant and Degree =====

    float DegToRad(float deg)
    {
        return deg * M_PI / 180;
    }
    
    float RadToDeg(float rad)
    {
        return rad * 180 / M_PI;
    }

//=====================================



//===== Vector2D =====

  // --> Builder
    Vector2D::Vector2D()
    {
        this->x = 0;
        this->y = 0;
        for (int i = 0; i < 2; i++)
        {
            this->xy[i] = 0;
        }
    }

    Vector2D::Vector2D(float a, float b)
    {
        this->x = a;
        this->y = b;
    }


  // --> Fonction
    float Vector2D::GetMagnitude() const
    {
        return (float)sqrt(pow(this->x, 2) + pow(this->y, 2));
    }
    
    float Vector2D::Dot(const Vector2D vec3)
    {
        return ((x * vec3.x) + (y * vec3.y));
    }
    
    void Vector2D::Normalize()
    {
        float norme = this->GetMagnitude();
        x           = x / norme;
        y           = y / norme;
    }


  // --> Operator
    Vector2D Vector2D::operator+(const Vector2D& vec3)
    {
        Vector2D vec;
        vec.x  = vec3.x + x;
        vec.y  = vec3.y + y;
        return   vec;
    }
    
    Vector2D Vector2D::operator-(const Vector2D& vec3)
    {
        Vector2D vec;
        vec.x  = x - vec3.x;
        vec.y  = y - vec3.y;
        return   vec;
    }
    
    Vector2D Vector2D::operator*(const Vector2D& vec3)
    {
        Vector2D vec;
        vec.x  = x * vec3.x;
        vec.y  = y * vec3.y;
        return   vec;
    }
    
    Vector2D Vector2D::operator*(const float& a)
    {
        Vector2D vec;
        vec.x  = x * a;
        vec.y  = y * a;
        return   vec;
    }
    
    Vector2D Vector2D::operator/(const float& a)
    {
        Vector2D vec;
        vec.x  = x / a;
        vec.y  = y / a;
        return   vec;
    }

//====================



//===== Vector3D =====

  // --> Builder
    Vector3D::Vector3D()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        for (int i = 0; i < 3; i++)
        {
            this->xyz[i] = 0;
        }
    }

    Vector3D::Vector3D(float a, float b, float c)
    {
        this->x = a;
        this->y = b;
        this->z = c;
    }


  // --> Fonction
    float Vector3D::GetMagnitude() const
    {
        return (float)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    }

    float Vector3D::Dot(const Vector3D vec3)
    {
        return ((x * vec3.x) + (y * vec3.y) + (z * vec3.z));
    }

    void Vector3D::Normalize()
    {
        float   norme = this->GetMagnitude();
        x = x / norme;
        y = y / norme;
        z = z / norme;
    }
    
    Vector3D Vector3D::CrossProduct(const Vector3D vec3)
    {
        Vector3D vec;
        vec.x = (vec3.z * y - vec3.y * z);
        vec.y = (vec3.x * z - vec3.z * x);
        vec.z = (vec3.y * x - vec3.x * y);
        return   vec;
    }


  // --> Operator
    Vector3D Vector3D::operator+(const Vector3D& vec3)
    {
        Vector3D vec;
        vec.x  = vec3.x + x;
        vec.y  = vec3.y + y;
        vec.z  = vec3.z + z;
        return   vec;
    }
    
    Vector3D Vector3D::operator-(const Vector3D& vec3)
    {
        Vector3D vec;
        vec.x  = x - vec3.x;
        vec.y  = y - vec3.y;
        vec.z  = z - vec3.z;
        return   vec;
    }
    
    Vector3D Vector3D::operator*(const Vector3D& vec3)
    {
        Vector3D vec;
        vec.x  = x * vec3.x;
        vec.y  = y * vec3.y;
        vec.z  = z * vec3.z;
        return   vec;
    }
    
    Vector3D Vector3D::operator*(const float& a)
    {
        Vector3D vec;
        vec.x  = x * a;
        vec.y  = y * a;
        vec.z  = z * a;
        return   vec;
    }
    
    Vector3D Vector3D::operator/(const float& a)
    {
        Vector3D vec;
        vec.x  = x / a;
        vec.y  = y / a;
        vec.z  = z / a;
        return   vec;
    }

//====================



//===== Vector4D =====

  // --> Builder
    Vector4D::Vector4D()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
        for (int i = 0; i < 4; i++)
        {
            this->xyz[i] = 0;
        }
    }

    Vector4D::Vector4D(float a, float b, float c, float d)
    {
        this->x = a;
        this->y = b;
        this->z = c;
        this->w = d;
    }

    Vector4D::Vector4D(const Vector3D& vec3, float _w)
    {
        this->x = vec3.x;
        this->y = vec3.y;
        this->z = vec3.z;
        this->w =     _w;
    }


  // --> Fonction
    float Vector4D::GetMagnitude() const
    {
        Vector4D temp{{x, y, z}, w};
        return (float)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    }
    
    void Vector4D::Homogenize()
    {
        if (w != 0)
        {
            x /= w;
            y /= w;
            z /= w;
        }
    }

    void Vector4D::Normalize()
    {
        float norme = this->GetMagnitude();
        x  /= norme;
        y  /= norme;
        z  /= norme;
    }

    Vector4D Vector4D::CrossProduct(const Vector3D vec4)
    {
        Vector4D vec;
        vec.x = (vec4.z * y - vec4.y * z);
        vec.y = (vec4.x * z - vec4.z * x);
        vec.z = (vec4.y * x - vec4.x * y);
        return   vec;
    }


  // --> Operator
    Vector4D Vector4D::operator+(const Vector4D& vec4)
    {
        Vector4D vec;
        vec.x = vec4.x + x;
        vec.y = vec4.y + y;
        vec.z = vec4.z + z;
        vec.w = vec4.w + w;
        return  vec;
    }
    
    Vector4D Vector4D::operator*(const Vector4D& vec4)
    {
        Vector4D vec;
        vec.x = vec4.x * x;
        vec.y = vec4.y * y;
        vec.z = vec4.z * z;
        vec.w = vec4.w * w;
        return  vec;
    }
    
    Vector4D Vector4D::operator*(const float& a)
    {
        Vector4D vec;
        vec.x  = x * a;
        vec.y  = y * a;
        vec.z  = z * a;
        vec.w  = w * a;
        return   vec;
    }

//====================



//===== Matrix3 =====

  // --> Builder
    Matrix3::Matrix3()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrixTab3[i][j] = 0.f;
            }
        }
    }
    
    Matrix3::Matrix3(const float a[3][3])
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrixTab3[i][j] = a[i][j];
            }
        }
    }
  // --> Function

    Matrix3 Matrix3::GetTransposeMat3()
    {
        Matrix3 matrix = Matrix3();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrix.matrixTab3[i][j] = this->matrixTab3[j][i];
            }
        }
        return matrix;
    }

    Matrix3 Matrix3::GetAdjugateMat3()
    {
        Matrix3 matrix = Matrix3();

        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                matrix.matrixTab3[i][j] = GetDeterminantMat2(this->matrixTab3[(i + 1) % 3][(j + 1) % 3], 
                                                             this->matrixTab3[(i + 2) % 3][(j + 1) % 3], 
                                                             this->matrixTab3[(i + 1) % 3][(j + 2) % 3], 
                                                             this->matrixTab3[(i + 2) % 3][(j + 2) % 3]);
                if ((i + j) % 2 == 1) 
                {
                    matrix.matrixTab3[i][j] *= -1;
                }
            }
        }

        return matrix;
    }

    Matrix3 Matrix3::GetInvertibleMat3()
    {
        return (this->GetAdjugateMat3().GetTransposeMat3() * (1 / GetDeterminantMat3(this->matrixTab3)));
    }


  // --> Operator
    Matrix3 Matrix3::operator*(const Matrix3& mat1)
    {
        Matrix3 mat;

        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            { 
                mat.matrixTab3[k][j] = matrixTab3[k][0] * mat1.matrixTab3[0][j] + matrixTab3[k][1] * mat1.matrixTab3[1][j] + matrixTab3[k][2] * mat1.matrixTab3[2][j];
            }
        } 

        return mat;
    }

    Vector3D Matrix3::operator*(const Vector3D& vec1)
    {
        Vector3D vec;
        vec.x = vec1.x * matrixTab3[0][0] + vec1.y * matrixTab3[0][1] + vec1.z * matrixTab3[0][2];
        vec.y = vec1.x * matrixTab3[1][0] + vec1.y * matrixTab3[1][1] + vec1.z * matrixTab3[1][2];
        vec.z = vec1.x * matrixTab3[2][0] + vec1.y * matrixTab3[2][1] + vec1.z * matrixTab3[2][2];
        return vec;
    }

//====================

//===== Matrix4 =====

  // --> Builder
    Matrix4::Matrix4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrixTab4[i][j] = 0.f;
            }
        }
    }

    Matrix4::Matrix4(const float a[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrixTab4[i][j] = a[i][j];
            }
        }
    }


  // --> Fonction
    Matrix4 Matrix4::GetTransposeMat4()
    {
        Matrix4 matrix = Matrix4();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix.matrixTab4[i][j] = this->matrixTab4[j][i];
            }
        }
        return matrix;
    }
  
    Matrix4 Matrix4::CreateTransformMatrix(const Vector3D& rotation, const Vector3D& position, const Vector3D& scale)
    {
        return  CreateTranslationMatrix(position) * CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
    }

    Matrix4 Matrix4::CreateTranslationMatrix(const Vector3D& translation)
    {
        float tab[4][4] =
        {
            {1, 0, 0, translation.x},
            {0, 1, 0, translation.y},
            {0, 0, 1, translation.z},
            {0, 0, 0, 1}
        };
        Matrix4 temp = tab;
        return temp;
    }

    Matrix4 Matrix4::CreateScaleMatrix(const Vector3D& scale)
    {
        float tab[4][4] =
        {
            {scale.x, 0, 0, 0},
            {0, scale.y, 0, 0},
            {0, 0, scale.z, 0},
            {0, 0, 0, 1}
        };
        Matrix4 temp = tab;
        return temp;
    }

    Matrix4 Matrix4::CreateXRotationMatrix(float angle)
    {
        float tab[4][4] =
        {
            {1, 0, 0, 0},
            {0, cosf(angle), -sinf(angle), 0},
            {0, sinf(angle), cosf(angle), 0},
            {0, 0, 0, 1},
        };
        Matrix4 temp = tab;
        return temp;
    }

    Matrix4 Matrix4::CreateYRotationMatrix(float angle)
    {
        float tab[4][4] =
        {
            {cosf(angle), 0, sinf(angle), 0},
            {0, 1, 0, 0},
            {-sinf(angle), 0, cosf(angle), 0},
            {0, 0, 0, 1}
        };

        Matrix4 temp = tab;
        return temp;
    }

    Matrix4 Matrix4::CreateZRotationMatrix(float angle)
    {
        float tab[4][4] =
        {
            {cosf(angle), -sinf(angle), 0, 0},
            {sinf(angle), cosf(angle), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
        };
        Matrix4 temp = tab;
        return tab;
    }

    //to be modified
    /*Matrix4 Matrix4::GetAdjugateMat4()
    {
        Matrix4 matrix = Matrix4();

        matrix.matrixTab4[0][0] = GetDeterminantMat3({ this->matrixTab4[1][1], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][1], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][1], this->matrixTab4[3][2], this->matrixTab4[3][3] });
        matrix.matrixTab4[0][1] = GetDeterminantMat3({ this->matrixTab4[1][0], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][2], this->matrixTab4[3][3] });
        matrix.matrixTab4[0][2] = GetDeterminantMat3({ this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][3] });
        matrix.matrixTab4[0][3] = GetDeterminantMat3({ this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][2] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][2] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][2] });

        matrix.matrixTab4[1][0] = GetDeterminantMat3({ this->matrixTab4[0][1], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[2][1], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][1], this->matrixTab4[3][2], this->matrixTab4[3][3] });
        matrix.matrixTab4[1][1] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][2], this->matrixTab4[3][3] });
        matrix.matrixTab4[1][2] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][3] });
        matrix.matrixTab4[1][3] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][2] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][2] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][2] });

        matrix.matrixTab4[2][0] = GetDeterminantMat3({ this->matrixTab4[0][1], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][1], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[3][1], this->matrixTab4[3][2], this->matrixTab4[3][3] });
        matrix.matrixTab4[2][1] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][2], this->matrixTab4[3][3] });
        matrix.matrixTab4[2][2] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][3] });
        matrix.matrixTab4[2][3] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][2] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][2] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][2] });

        matrix.matrixTab4[3][0] = GetDeterminantMat3({ this->matrixTab4[0][1], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][1], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][1], this->matrixTab4[2][2], this->matrixTab4[2][3] });
        matrix.matrixTab4[3][1] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][2], this->matrixTab4[2][3] });
        matrix.matrixTab4[3][2] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][3] });
        matrix.matrixTab4[3][3] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][2] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][2] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][2] });

        return matrix;
    }*/

    Matrix4 Matrix4::GetAdjugateMat4()
    {
        Matrix4 matrix = Matrix4();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix.matrixTab4[i][j] = GetDeterminantMat3({ this->matrixTab4[(i + 1) % 4][(j + 1) % 4], this->matrixTab4[(i + 1) % 4][(j + 2) % 4], this->matrixTab4[(i + 1) % 4][(j + 3) % 4] },
                                                             { this->matrixTab4[(i + 2) % 4][(j + 1) % 4], this->matrixTab4[(i + 2) % 4][(j + 2) % 4], this->matrixTab4[(i + 2) % 4][(j + 3) % 4] },
                                                             { this->matrixTab4[(i + 3) % 4][(j + 1) % 4], this->matrixTab4[(i + 3) % 4][(j + 2) % 4], this->matrixTab4[(i + 3) % 4][(j + 3) % 4] });
            }
        }

        return matrix;
    }


    Matrix4 Matrix4::GetInvertibleMat4()
    {
        return (this->GetAdjugateMat4().GetTransposeMat4() * (1 / GetDeterminantMat4(*this)));
    }
    
    Matrix4 Matrix4::GetProjection(const float& fov, const float& n, const float& f)
    {
        float s = 1 / tanf((fov / 2) * (M_PI / 180));
        float c = f / (f - n);
    
        float projectionMatrix[4][4] = {
            {s, 0.f, 0.f, 0.f},
            {0.f, s, 0.f, 0.f},
            {0.f, 0.f, -c, -(c * n)},
            {0.f, 0.f, -1.f, 0.f},
        };
        return projectionMatrix;
    }


  // --> Operator
    Matrix4 Matrix4::operator*(const Matrix4& mat1)
    {
        Matrix4 mat;
    
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mat.matrixTab4[i][j] = matrixTab4[i][0] * mat1.matrixTab4[0][j] + matrixTab4[i][1] * mat1.matrixTab4[1][j] + matrixTab4[i][2] * mat1.matrixTab4[2][j] + matrixTab4[i][3] * mat1.matrixTab4[3][j];
            }
        }
    
        return mat;
    }

    Vector4D Matrix4::operator*(const Vector4D& vec1)
    {
        Vector4D vec;
        vec.x = vec1.x * matrixTab4[0][0] + vec1.y * matrixTab4[0][1] + vec1.z * matrixTab4[0][2] + vec1.w * matrixTab4[0][3];
        vec.y = vec1.x * matrixTab4[1][0] + vec1.y * matrixTab4[1][1] + vec1.z * matrixTab4[1][2] + vec1.w * matrixTab4[1][3];
        vec.z = vec1.x * matrixTab4[2][0] + vec1.y * matrixTab4[2][1] + vec1.z * matrixTab4[2][2] + vec1.w * matrixTab4[2][3];
        vec.w = vec1.x * matrixTab4[3][0] + vec1.y * matrixTab4[3][1] + vec1.z * matrixTab4[3][2] + vec1.w * matrixTab4[3][3];
        return vec;
    }

    Matrix4 operator*(const Matrix4& a, const Matrix4& b)
    {
        Matrix4 c = Matrix4();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    c.matrixTab4[i][j] += a.matrixTab4[i][k] * b.matrixTab4[k][j];
                }
            }
        }

        return c;
    }


    Matrix4 operator*(const Matrix4& a, const float b)
    {
        Matrix4 c = Matrix4();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                c.matrixTab4[i][j] = a.matrixTab4[i][j] * b;
            }
        }

        return c;
    }

    Matrix3 operator*(const Matrix3& a, const Matrix3& b)
    {
        Matrix3 c = Matrix3();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    c.matrixTab3[i][j] += a.matrixTab3[i][k] * b.matrixTab3[k][j];
                }
            }
        }

        return c;
    }

    Matrix3 operator*(const Matrix3& a, const float b)
    {
        Matrix3 c = Matrix3();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                c.matrixTab3[i][j] = a.matrixTab3[i][j] * b;
            }
        }

        return c;
    }


    Vector4D operator*(const Matrix4& a, const Vector4D& b)
    {
        Vector4D c = Vector4D();

        c.x = a.matrixTab4[0][0] * b.x + a.matrixTab4[0][1] * b.y + a.matrixTab4[0][2] * b.z + a.matrixTab4[0][3] * b.w;
        c.y = a.matrixTab4[1][0] * b.x + a.matrixTab4[1][1] * b.y + a.matrixTab4[1][2] * b.z + a.matrixTab4[1][3] * b.w;
        c.z = a.matrixTab4[2][0] * b.x + a.matrixTab4[2][1] * b.y + a.matrixTab4[2][2] * b.z + a.matrixTab4[2][3] * b.w;
        c.w = a.matrixTab4[3][0] * b.x + a.matrixTab4[3][1] * b.y + a.matrixTab4[3][2] * b.z + a.matrixTab4[3][3] * b.w;

        return c;
    }

    Vector4D operator*(const Vector4D& b, const Matrix4& a)
    {
        Vector4D c = Vector4D();

        c.x = a.matrixTab4[0][0] * b.x + a.matrixTab4[0][1] * b.y + a.matrixTab4[0][2] * b.z + a.matrixTab4[0][3] * b.w;
        c.y = a.matrixTab4[1][0] * b.x + a.matrixTab4[1][1] * b.y + a.matrixTab4[1][2] * b.z + a.matrixTab4[1][3] * b.w;
        c.z = a.matrixTab4[2][0] * b.x + a.matrixTab4[2][1] * b.y + a.matrixTab4[2][2] * b.z + a.matrixTab4[2][3] * b.w;
        c.w = a.matrixTab4[3][0] * b.x + a.matrixTab4[3][1] * b.y + a.matrixTab4[3][2] * b.z + a.matrixTab4[3][3] * b.w;

        return c;
    }

//====================

// -- > More Fonction 
// find the maximum between 2 points
int checkMax2(int a, int b)
{
    return (a < b) ? b : a;
}

// Find the minimum between 2 points
int checkMin2(int a, int b)
{
    return (a < b) ? a : b;
}

// find the maximum between 3 points
int checkMax3(int a, int b, int c)
{
    int d;
    d = a < b ? b : a;
    return (d < c) ? c : d;
}

// Find the minimum between 3 points
int checkMin3(int a, int b, int c)
{
    int d;
    d = a > b ? b : a;
    return (d > c) ? c : d;
}

// Function to find the barycenter
float edgeFunction(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

float GetDeterminantMat2(const float a, const float b, const float c, const float d)
{
    return (a * d - b * c);
}

float GetDeterminantMat3(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    return (
        a.x * GetDeterminantMat2(b.y, b.z, c.y, c.z)
        - a.y * GetDeterminantMat2(b.x, b.z, c.x, c.z)
        + a.z * GetDeterminantMat2(b.x, b.y, c.x, c.y)
        );
}

float GetDeterminantMat3(const float tab[3][3])
{
    return (
        tab[0][0] * GetDeterminantMat2(tab[1][1], tab[1][2], tab[2][1], tab[2][2])
        - tab[0][1] * GetDeterminantMat2(tab[1][0], tab[1][2], tab[2][0], tab[2][2])
        + tab[0][2] * GetDeterminantMat2(tab[1][0], tab[1][1], tab[2][0], tab[2][1])
        );
}

float GetDeterminantMat4(const Matrix4& a)
{
    return(
        a.matrixTab4[0][0] * GetDeterminantMat3({ a.matrixTab4[1][1], a.matrixTab4[1][2], a.matrixTab4[1][3] }, { a.matrixTab4[2][1], a.matrixTab4[2][2], a.matrixTab4[2][3] }, { a.matrixTab4[3][1], a.matrixTab4[3][2], a.matrixTab4[3][3] })
        - a.matrixTab4[0][1] * GetDeterminantMat3({ a.matrixTab4[1][0], a.matrixTab4[1][2], a.matrixTab4[1][3] }, { a.matrixTab4[2][0], a.matrixTab4[2][2], a.matrixTab4[2][3] }, { a.matrixTab4[3][0], a.matrixTab4[3][2], a.matrixTab4[3][3] })
        + a.matrixTab4[0][2] * GetDeterminantMat3({ a.matrixTab4[1][0], a.matrixTab4[1][1], a.matrixTab4[1][3] }, { a.matrixTab4[2][0], a.matrixTab4[2][1], a.matrixTab4[2][3] }, { a.matrixTab4[3][0], a.matrixTab4[3][1], a.matrixTab4[3][3] })
        - a.matrixTab4[0][3] * GetDeterminantMat3({ a.matrixTab4[1][0], a.matrixTab4[1][1], a.matrixTab4[1][2] }, { a.matrixTab4[2][0], a.matrixTab4[2][1], a.matrixTab4[2][2] }, { a.matrixTab4[3][0], a.matrixTab4[3][1], a.matrixTab4[3][2] })
        );
}

float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

Vector3D operator*(const float b, const Vector3D& a)
{
    Vector3D c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

Quaternion::Quaternion() {

}


Quaternion::Quaternion(float uS, Vector3D& uV)  {
    s = uS;
    v = uV;
}


Quaternion::~Quaternion() {

}


Quaternion::Quaternion(const Quaternion& value) {

    s = value.s;
    v = value.v;

};


Quaternion& Quaternion::operator=(const Quaternion& value) {

    s = value.s;
    v = value.v;

    return *this;
};



void Quaternion::operator+=(const Quaternion& q) {

    s += q.s;
    v =v+ q.v;

}

Quaternion Quaternion::operator+(const Quaternion& q) {

    float scalar = s + q.s;
    Vector3D imaginary = v + q.v;

    return Quaternion(scalar, imaginary);
}

void Quaternion::operator-=(const Quaternion& q) {

    s -= q.s;
    v =v- q.v;
}

Quaternion Quaternion::operator-(const Quaternion& q) {

    float scalar = s - q.s;
    Vector3D imaginary = v - q.v;

    return Quaternion(scalar, imaginary);
}


/*void Quaternion::operator*=(const Quaternion& q) {

    (*this) = multiply(q);
}*/

Quaternion Quaternion::operator*(const Quaternion& q) {

    float scalar = s * q.s - v.Dot(q.v);

    Vector3D imaginary =  s* q.v  + v * q.s + v.CrossProduct(q.v);

    return Quaternion(scalar, imaginary);

}


void Quaternion::operator*=(const float value) {

    s *= value;
    v =v* value;
}


Quaternion Quaternion::operator*(const float value) {

    float scalar = s * value;
    Vector3D imaginary = v * value;

    return Quaternion(scalar, imaginary);

}

Quaternion Quaternion::operator*(const Vector3D& uValue) {


    float sPart = -(v.x * uValue.x + v.y * uValue.y + v.z * uValue.z);
    float xPart = s * uValue.x + v.y * uValue.z - v.z * uValue.y;
    float yPart = s * uValue.y + v.z * uValue.x - v.x * uValue.z;
    float zPart = s * uValue.z + v.x * uValue.y - v.y * uValue.x;

    Vector3D vectorPart(xPart, yPart, zPart);
    Quaternion result(sPart, vectorPart);

    return result;

}


float Quaternion::dot(Quaternion& q) {

    return s * q.s + v.x * q.v.x + v.y * q.v.y + v.z * q.v.z;

}


float Quaternion::norm() {

    float scalar = s * s;
    float imaginary = v.Dot(v);

    return sqrt(scalar + imaginary);
}


void Quaternion::normalize() {

    if (norm() != 0) {

        float normValue = 1 / norm();

        s = s* normValue;
        v = v* normValue;
    }
}

Quaternion Quaternion::conjugate() {

    float scalar = s;
    Vector3D imaginary = v * (-1);

    return Quaternion(scalar, imaginary);
}

Quaternion Quaternion::inverse() {

    float absoluteValue = norm();
    absoluteValue *= absoluteValue;
    absoluteValue = 1 / absoluteValue;

    Quaternion conjugateValue = conjugate();

    float scalar = conjugateValue.s * (absoluteValue);
    Vector3D imaginary = conjugateValue.v * (absoluteValue);

    return Quaternion(scalar, imaginary);
}

void Quaternion::inverse(Quaternion& q) {

    Quaternion dummy = q.inverse();

    q = dummy;
}


void Quaternion::convertToUnitNormQuaternion() {

    float angle = DegToRad(s);

    v.Normalize();
    s = cosf(angle * 0.5);
    v = v * sinf(angle * 0.5);

}


Matrix4 Quaternion::transformQuaternionToMatrix4() {

    Matrix4 m;

    m.matrixTab4[0][0] = 2 * (s * s + v.x * v.x) - 1;
    m.matrixTab4[1][0] = 2 * (v.x * v.y + s * v.z);
    m.matrixTab4[2][0] = 2 * (v.x * v.z - s * v.y);
    m.matrixTab4[3][0] = 0;
   
    
    m.matrixTab4[0][1] = 2 * (v.x * v.y - s * v.z);
    m.matrixTab4[1][1] = 2 * (s * s + v.y * v.y) - 1;
    m.matrixTab4[2][1] = 2 * (v.y * v.z + s * v.x);
    m.matrixTab4[3][1] = 0;
    
    m.matrixTab4[0][2] = 2 * (v.x * v.z + s * v.y);
    m.matrixTab4[1][2] = 2 * (v.y * v.z - s * v.x);
    m.matrixTab4[2][2] = 2 * (s * s + v.z * v.z) - 1;
    m.matrixTab4[3][2] = 0;
    
    m.matrixTab4[0][3] = 0;
    m.matrixTab4[1][3] = 0;
    m.matrixTab4[2][3] = 0;
    m.matrixTab4[3][3] = 1;
   
    return m;
}

void Quaternion::transformEulerAnglesToQuaternion(float x, float y, float z) {

    x = DegToRad(x);
    y = DegToRad(y);
    z = DegToRad(z);

    x = x / 2;
    y = y / 2;
    z = z / 2;

    s = cos(z) * cos(y) * cos(x) + sin(z) * sin(y) * sin(x);
    v.x = cos(z) * cos(y) * sin(x) - sin(z) * sin(y) * cos(x);
    v.y = cos(z) * sin(y) * cos(x) + sin(z) * cos(y) * sin(x);
    v.z = sin(z) * cos(y) * cos(x) - cos(z) * sin(y) * sin(x);


}


Vector3D Quaternion::transformQuaternionToEulerAngles() {

    // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
    //	0	3	6
    //	1	4	7
    //	2	5	8


    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    float test = 2 * (v.x * v.z - s * v.y);

    if (test != 1 && test != -1) {

        x = atan2(v.y * v.z + s * v.x, 0.5 - (v.x * v.x + v.y * v.y));
        y = asin(-2 * (v.x * v.z - s * v.y));
        z = atan2(v.x * v.y + s * v.z, 0.5 - (v.y * v.y + v.z * v.z));

    }
    else if (test == 1) {
        z = atan2(v.x * v.y + s * v.z, 0.5 - (v.y * v.y + v.z * v.z));
        y = -M_PI / 2.0;
        x = -z + atan2(v.x * v.y - s * v.z, v.x * v.z + s * v.y);

    }
    else if (test == -1) {

        z = atan2(v.x * v.y + s * v.z, 0.5 - (v.y * v.y + v.z * v.z));
        y = M_PI / 2.0;
        x = z + atan2(v.x * v.y - s * v.z, v.x * v.z + s * v.y);

    }

    x = RadToDeg(x);
    y = RadToDeg(y);
    z = RadToDeg(z);

    Vector3D euler(x, y, z);

    return euler;
}

#pragma mark-Matrix to quaternion
void Quaternion::transformMatrix3nToQuaternion(Matrix3& uMatrix) {

    float trace = uMatrix.matrixTab9[0] + uMatrix.matrixTab9[4] + uMatrix.matrixTab9[8];

    if (trace > 0) {      //s=4*qw

        s = 0.5 * sqrt(1 + trace);
        float S = 0.25 / s;

        v.x = S * (uMatrix.matrixTab9[5] - uMatrix.matrixTab9[7]);
        v.y = S * (uMatrix.matrixTab9[6] - uMatrix.matrixTab9[2]);
        v.z = S * (uMatrix.matrixTab9[1] - uMatrix.matrixTab9[3]);

    }
    else if (uMatrix.matrixTab9[0] > uMatrix.matrixTab9[4] && uMatrix.matrixTab9[0] > uMatrix.matrixTab9[8]) { 

        v.x = 0.5 * sqrt(1 + uMatrix.matrixTab9[0] - uMatrix.matrixTab9[4] - uMatrix.matrixTab9[8]);
        float X = 0.25 / v.x;

        v.y = X * (uMatrix.matrixTab9[3] + uMatrix.matrixTab9[1]);
        v.z = X * (uMatrix.matrixTab9[6] + uMatrix.matrixTab9[2]);
        s = X * (uMatrix.matrixTab9[5] - uMatrix.matrixTab9[7]);

    }
    else if (uMatrix.matrixTab9[4] > uMatrix.matrixTab9[8]) {

        v.y = 0.5 * sqrt(1 - uMatrix.matrixTab9[0] + uMatrix.matrixTab9[4] - uMatrix.matrixTab9[8]);
        float Y = 0.25 / v.y;
        v.x = Y * (uMatrix.matrixTab9[3] + uMatrix.matrixTab9[1]);
        v.z = Y * (uMatrix.matrixTab9[7] + uMatrix.matrixTab9[5]);
        s = Y * (uMatrix.matrixTab9[6] - uMatrix.matrixTab9[2]);

    }
    else { 

        v.z = 0.5 * sqrt(1 - uMatrix.matrixTab9[0] - uMatrix.matrixTab9[4] + uMatrix.matrixTab9[8]);
        float Z = 0.25 / v.z;
        v.x = Z * (uMatrix.matrixTab9[6] + uMatrix.matrixTab9[2]);
        v.y = Z * (uMatrix.matrixTab9[7] + uMatrix.matrixTab9[5]);
        s = Z * (uMatrix.matrixTab9[1] - uMatrix.matrixTab9[3]);
    }


}

