#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **create_matrix(int row, int col); // ���� �޸� �Ҵ����� 2���� �迭�� ����� ��� ����
void print_matrix(int **matrix, int row, int col);  // ����� ��� ���� ���
int free_matrix(int **matrix, int row, int col);    // �޸𸮿� �������� �Ҵ�� ��� ����
int fill_data(int **matrix, int row, int col);      // ��Ŀ� 0 ~ 19������ ������ ������ ä���
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);   // ��� A�� B�� ��
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col); // ��� A�� B�� ��
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);  // ����� ��ġ��� ����
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col); // ��� A�� ��� A�� ��ġ����� ��

int main()
{

    char command;
    printf("[----- [����â]  [2021040021] -----]\n");

    int row, col; // row(��), col(��)
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);  // ������ ����� ��� ���� �Է�

    int **matrix_a = create_matrix(row, col);   // row * col ��� A ����
    int **matrix_b = create_matrix(row, col);   // row * col ��� B ����
    int **matrix_a_t = create_matrix(col, row); // ��� A�� ��ġ����� ǥ���� col * row ��� ����

    if (matrix_a == NULL || matrix_b == NULL) // matrix_a �Ǵ� matrix_b�� ����Ű�� �ּҰ� ���� ��� 
    {
        return -1;      // -1 ��ȯ, ������ ����
    }
    
    printf("Matrix Created.\n");   // ��� ������ �����ߴٴ� ���� ���

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // ��ɾ� �Է�

        switch (command)
        {
        case 'z':         // z �Ǵ� Z �Է����� ���
        case 'Z':
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col);   // ��� A�� 0 ~ 19������ ������ ������ ä���
            fill_data(matrix_b, row, col);   // ��� B�� 0 ~ 19������ ������ ������ ä���
            break;
        case 'p':
        case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);   // ��� A�� ���� ���
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);  // ��� B�� ���� ���
            break;
        case 'a':       // a �Ǵ� A �Է����� ���
        case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);  
            // ��� A�� B�� ���� ��Ÿ���� ����� �����ϰ� ���, �������� �Ҵ�� ���� ����
            break;
        case 's':   // s �Ǵ� S �Է����� ���
        case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            // ��� A�� B�� ���� ��Ÿ���� ����� �����ϰ� ���, �������� �Ҵ�� ���� ����
            break;
        case 't': // t �Ǵ� T �Է����� ���
        case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  
            // ��� A�� ��ġ����� ������ matrix_a_t�� �ִ´�. 
            print_matrix(matrix_a_t, col, row); // ��� A�� ��ġ��� ���
            break;
        case 'm': // m �Ǵ� M �Է����� ���
        case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);   
            // ��� A�� ��ġ����� ������ matrix_a_t�� �ִ´�. 
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            // ��� A�� A�� ��ġ����� ���� ��Ÿ���� ����� �����ϰ� ���, �������� �Ҵ�� ���� ����
            break;
        case 'q': // q �Ǵ� Q �Է����� ���
        case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);  // ��� A�� ��ġ����� ǥ���ϴ� matrix_a_t�� ���� ����
            free_matrix(matrix_a, row, col);    // ��� A�� ���� ����
            free_matrix(matrix_b, row, col);    // ��� B�� ���� ����
            break;
        default: // �� ���� ��ɾ �Է����� ���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  // �����϶�� ��� ���
            break;
        }

    } while (command != 'q' && command != 'Q');  // q �Ǵ� Q �Է��� ������ �ݺ�

    return 1; // ���� ����
}

int **create_matrix(int row, int col) // ���� �޸� �Ҵ����� 2���� �迭�� ����� ��� ����
{
    if (row <= 0 || col <= 0)      // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the sizes of row and col!\n");    // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return NULL; 
    }

    int **matrix = (int **)malloc(sizeof(int *) * row);     
    // ��(row)*4����Ʈ(32��Ʈ �ü���� �� �������� ũ��)��ŭ�� ������ �����ϰ� �� �ּҸ� matrix�� �Ҵ�

    for (int i = 0; i < row; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * col);      
        // 4����Ʈ * ��(col)��ŭ�� ������ ��(row)�� ������ŭ �����,
        // �� �������� �ּҸ� matrix���� ������ �� �ִ� ������ ���� �Ҵ��Ѵ�. 
    }

    if (matrix == NULL)  // ���� matrix�� ����Ű�� �ּҰ� ���� ��� 
    {
        printf("Memory Allocation Failed.\n");   // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return NULL;  
    }

    return matrix;  // ������ matrix�� �ּ� ��ȯ
}

void print_matrix(int **matrix, int row, int col) // matrix�� ��� ���� ���
{
    if (row <= 0 || col <= 0)      // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");     // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return;   
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%3d ", matrix[i][j]);     // ����� ��� ���� ���
        }
        printf("\n");
    }
    printf("\n");
    if (matrix == NULL)   // ���� matrix�� ����Ű�� �ּҰ� ���� ��� 
    {
        printf("Memory Allocation Failed.\n");    // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return;   
    }

    return;
}

int free_matrix(int **matrix, int row, int col)
{
    if (row <= 0 || col <= 0)      // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");  // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);    // matrix�� ����Ű�� ������ ����Ű�� ���� ����
    }

    free(matrix);       // matrix�� ����Ű�� ���� ����
    return 1;
}

int fill_data(int **matrix, int row, int col) // 0 ~ 19 ������ ���� ���� ���������� ä���.  // ����
{
    if (row <= 0 || col <= 0)      // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");      // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 20; // ��� �� ���п� 0 ~ 19 ������ ���� �Ҵ�
        }
    }

    if (matrix == NULL)     // ���� matrix�� ����Ű�� �ּҰ� ���� ���
    {
        printf("Memory Allocation Failed.\n");    // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return -1;
    }
    return 1;
}

int addition_matrix(int **matrix_a, int **matrix_b, int row, int col)    // ��� A�� B�� ��
{
    if (row <= 0 || col <= 0)        // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");      // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return -1;
    }

    int **matrix_sum = create_matrix(row, col); 
    // ��� A�� ��� B�� ���� ������ row * col ��� matrix_sum ����

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];     // ��� A�� ��� B�� ���е��� ��
        }
    }

    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL)  
    // ���� matrix_a �Ǵ� matrix_b �Ǵ� matrix_sum�� ����Ű�� �ּҰ� ���� ���
    {
        printf("Memory Allocation Failed.\n");      // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return -1;
    }

    print_matrix(matrix_sum, row, col);     // matrix_sum�� ���� ���
    free_matrix(matrix_sum, row, col);      // matrix_sum���κ��� ������ �� �ִ� ��� ���� ����
    return 1;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col)   // ��� A�� B�� ��
{
    if (row <= 0 || col <= 0)           // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");     // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return -1;
    }

    int **matrix_sub = create_matrix(row, col);
    // ��� A�� ��� B�� ���� ������ row * col ��� matrix_sub ����

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];     // ��� A�� ��� B�� ���е��� ��
        }
    }

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL)  
    // ���� matrix_a �Ǵ� matrix_b �Ǵ� matrix_sub�� ����Ű�� �ּҰ� ���� ���
    {
        printf("Memory Allocation Failed.\n");      // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return -1;
    }

    print_matrix(matrix_sub, row, col);    // matrix_sub�� ���� ���
    free_matrix(matrix_sub, row, col);     // matrix_sub�κ��� ������ �� �ִ� ��� ���� ����

    return 1;
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col) // ����� ��ġ��� ����
{
    if (row <= 0 || col <= 0)      // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");      // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return -1;
    }

    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            matrix_t[j][i] = matrix[i][j];     // matrix�� ���� matrix_t�� ������ �ٲ۴�.
        }
    }

    if (matrix == NULL || matrix_t == NULL)   // ���� matrix �Ǵ� matrix_t�� ����Ű�� �ּҰ� ���� ���
    {
        printf("Memory Allocation Failed.\n");  // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return -1;
    }

    return 1;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col)   // ��� A�� ��� A�� ��ġ����� ��
{
    if (row <= 0 || col <= 0)    // row �Ǵ� col�� 0������ ��� ��, ���������� �Է��� ���
    {
        printf("Check the size of row and col!\n");     // ��� ���� ũ�⸦ Ȯ���϶�� ��� ���
        return -1;
    }

    int **matrix_axt = create_matrix(row, col); 
    // ��� A�� ��� A�� ��ġ����� ���� ������ ��� matrix_set ����

    for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++)   
    // ����� ��������̹Ƿ� ���� ������ŭ �ݺ��Ѵ�. 
    {
        for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++)
        {
            int temp = 0;
            for (int matrix_col = 0; matrix_col < col; matrix_col++)
            {
                temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];        
                // matrix_a�� 0��° ��� matrix_t�� 0��° ���� ������ ���Ѵ�. 
                // �������� matrix_a�� 1��° ��� matrix_t�� 1��° ���� ������ ���Ѵ�. (�ݺ�...)
                // �̷��� 0��°���� row-1��ŭ ����� �ݺ��Ѵ�.
            }
            matrix_axt[matrix_a_row][matrix_t_row] = temp;  
            // ������ �� ���� ���� temp�� matrix_axt�� ���п� �ִ´�. 
            // �̰��� ����� ����ŭ �ݺ��Ѵ�. �׷��� �� �྿ ä������.
        }
    }

    if (matrix_t == NULL || matrix_axt == NULL)     // ���� matrix_t �Ǵ� matrix_axt�� ����Ű�� �ּҰ� ���� ���
    {
        printf("Memory Allocation Failed.\n");      // ���� �޸� �Ҵ翡 �����ߴٴ� �����޽��� ���
        return -1;
    }

    print_matrix(matrix_axt, row, row);            // matrix_axt�� ���� ���
    free_matrix(matrix_axt, row, col);             // matrix_axt�κ��� ������ �� �ִ� ��� ���� ����
    return 1;
}