#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **create_matrix(int row, int col); // 동적 메모리 할당으로 2차원 배열을 만들어 행렬 생성
void print_matrix(int **matrix, int row, int col);  // 행렬의 모든 성분 출력
int free_matrix(int **matrix, int row, int col);    // 메모리에 동적으로 할당된 행렬 해제
int fill_data(int **matrix, int row, int col);      // 행렬에 0 ~ 19까지의 임의의 값으로 채우기
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);   // 행렬 A와 B의 합
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col); // 행렬 A와 B의 차
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);  // 행렬의 전치행렬 생성
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col); // 행렬 A와 행렬 A의 전치행렬의 곱

int main()
{

    char command;
    printf("[----- [복무창]  [2021040021] -----]\n");

    int row, col; // row(행), col(열)
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);  // 생성할 행렬의 행과 열을 입력

    int **matrix_a = create_matrix(row, col);   // row * col 행렬 A 생성
    int **matrix_b = create_matrix(row, col);   // row * col 행렬 B 생성
    int **matrix_a_t = create_matrix(col, row); // 행렬 A의 전치행렬을 표현할 col * row 행렬 생성

    if (matrix_a == NULL || matrix_b == NULL) // matrix_a 또는 matrix_b가 가리키는 주소가 없을 경우 
    {
        return -1;      // -1 반환, 비정상 종료
    }
    
    printf("Matrix Created.\n");   // 행렬 생성에 성공했다는 문구 출력

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
        scanf(" %c", &command); // 명령어 입력

        switch (command)
        {
        case 'z':         // z 또는 Z 입력했을 경우
        case 'Z':
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col);   // 행렬 A에 0 ~ 19까지의 임의의 값으로 채우기
            fill_data(matrix_b, row, col);   // 행렬 B에 0 ~ 19까지의 임의의 값으로 채우기
            break;
        case 'p':
        case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);   // 행렬 A의 값들 출력
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);  // 행렬 B의 값들 출력
            break;
        case 'a':       // a 또는 A 입력했을 경우
        case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);  
            // 행렬 A와 B의 합을 나타내는 행렬을 생성하고 출력, 동적으로 할당된 공간 해제
            break;
        case 's':   // s 또는 S 입력했을 경우
        case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            // 행렬 A와 B의 차를 나타내는 행렬을 생성하고 출력, 동적으로 할당된 공간 해제
            break;
        case 't': // t 또는 T 입력했을 경우
        case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  
            // 행렬 A의 전치행렬을 생성한 matrix_a_t에 넣는다. 
            print_matrix(matrix_a_t, col, row); // 행렬 A의 전치행렬 출력
            break;
        case 'm': // m 또는 M 입력했을 경우
        case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);   
            // 행렬 A의 전치행렬을 생성한 matrix_a_t에 넣는다. 
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            // 행렬 A와 A의 전치행렬의 곱을 나타내는 행렬을 생성하고 출력, 동적으로 할당된 공간 해제
            break;
        case 'q': // q 또는 Q 입력했을 경우
        case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);  // 행렬 A의 전치행렬을 표현하는 matrix_a_t의 공간 해제
            free_matrix(matrix_a, row, col);    // 행렬 A의 공간 해제
            free_matrix(matrix_b, row, col);    // 행렬 B의 공간 해제
            break;
        default: // 그 밖의 명령어를 입력했을 경우
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  // 집중하라는 경고문 출력
            break;
        }

    } while (command != 'q' && command != 'Q');  // q 또는 Q 입력할 때까지 반복

    return 1; // 정상 종료
}

int **create_matrix(int row, int col) // 동적 메모리 할당으로 2차원 배열을 만들어 행렬 생성
{
    if (row <= 0 || col <= 0)      // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the sizes of row and col!\n");    // 행과 열의 크기를 확인하라는 경고문 출력
        return NULL; 
    }

    int **matrix = (int **)malloc(sizeof(int *) * row);     
    // 행(row)*4바이트(32비트 운영체제일 때 포인터의 크기)만큼의 공간을 생성하고 그 주소를 matrix에 할당

    for (int i = 0; i < row; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * col);      
        // 4바이트 * 열(col)만큼의 공간을 행(row)의 개수만큼 만들고,
        // 그 공간들의 주소를 matrix에서 접근할 수 있는 공간에 각각 할당한다. 
    }

    if (matrix == NULL)  // 만약 matrix가 가리키는 주소가 없을 경우 
    {
        printf("Memory Allocation Failed.\n");   // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return NULL;  
    }

    return matrix;  // 생성된 matrix의 주소 반환
}

void print_matrix(int **matrix, int row, int col) // matrix의 모든 성분 출력
{
    if (row <= 0 || col <= 0)      // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");     // 행과 열의 크기를 확인하라는 경고문 출력
        return;   
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%3d ", matrix[i][j]);     // 행렬의 모든 성분 출력
        }
        printf("\n");
    }
    printf("\n");
    if (matrix == NULL)   // 만약 matrix가 가리키는 주소가 없을 경우 
    {
        printf("Memory Allocation Failed.\n");    // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return;   
    }

    return;
}

int free_matrix(int **matrix, int row, int col)
{
    if (row <= 0 || col <= 0)      // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");  // 행과 열의 크기를 확인하라는 경고문 출력
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);    // matrix가 가리키는 공간이 가리키는 공간 해제
    }

    free(matrix);       // matrix가 가리키는 공간 해제
    return 1;
}

int fill_data(int **matrix, int row, int col) // 0 ~ 19 사이의 값을 갖는 랜덤값으로 채운다.  // 성공
{
    if (row <= 0 || col <= 0)      // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");      // 행과 열의 크기를 확인하라는 경고문 출력
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 20; // 행렬 각 성분에 0 ~ 19 사이의 난수 할당
        }
    }

    if (matrix == NULL)     // 만약 matrix가 가리키는 주소가 없을 경우
    {
        printf("Memory Allocation Failed.\n");    // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return -1;
    }
    return 1;
}

int addition_matrix(int **matrix_a, int **matrix_b, int row, int col)    // 행렬 A와 B의 합
{
    if (row <= 0 || col <= 0)        // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");      // 행과 열의 크기를 확인하라는 경고문 출력
        return -1;
    }

    int **matrix_sum = create_matrix(row, col); 
    // 행렬 A와 행렬 B의 합을 저장할 row * col 행렬 matrix_sum 생성

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];     // 행렬 A와 행렬 B의 성분들의 합
        }
    }

    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL)  
    // 만약 matrix_a 또는 matrix_b 또는 matrix_sum이 가리키는 주소가 없을 경우
    {
        printf("Memory Allocation Failed.\n");      // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return -1;
    }

    print_matrix(matrix_sum, row, col);     // matrix_sum의 성분 출력
    free_matrix(matrix_sum, row, col);      // matrix_sum으로부터 접근할 수 있는 모든 공간 해제
    return 1;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col)   // 행렬 A와 B의 차
{
    if (row <= 0 || col <= 0)           // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");     // 행과 열의 크기를 확인하라는 경고문 출력
        return -1;
    }

    int **matrix_sub = create_matrix(row, col);
    // 행렬 A와 행렬 B의 합을 저장할 row * col 행렬 matrix_sub 생성

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];     // 행렬 A와 행렬 B의 성분들의 차
        }
    }

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL)  
    // 만약 matrix_a 또는 matrix_b 또는 matrix_sub이 가리키는 주소가 없을 경우
    {
        printf("Memory Allocation Failed.\n");      // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return -1;
    }

    print_matrix(matrix_sub, row, col);    // matrix_sub의 성분 출력
    free_matrix(matrix_sub, row, col);     // matrix_sub로부터 접근할 수 있는 모든 공간 해제

    return 1;
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col) // 행렬의 전치행렬 생성
{
    if (row <= 0 || col <= 0)      // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");      // 행과 열의 크기를 확인하라는 경고문 출력
        return -1;
    }

    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            matrix_t[j][i] = matrix[i][j];     // matrix의 열을 matrix_t의 행으로 바꾼다.
        }
    }

    if (matrix == NULL || matrix_t == NULL)   // 만약 matrix 또는 matrix_t가 가리키는 주소가 없을 경우
    {
        printf("Memory Allocation Failed.\n");  // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return -1;
    }

    return 1;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col)   // 행렬 A와 행렬 A의 전치행렬의 곱
{
    if (row <= 0 || col <= 0)    // row 또는 col이 0이하일 경우 즉, 비정상적인 입력일 경우
    {
        printf("Check the size of row and col!\n");     // 행과 열의 크기를 확인하라는 경고문 출력
        return -1;
    }

    int **matrix_axt = create_matrix(row, col); 
    // 행렬 A와 행렬 A의 전치행렬의 곱을 저장할 행렬 matrix_set 생성

    for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++)   
    // 행렬은 정방행렬이므로 행의 개수만큼 반복한다. 
    {
        for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++)
        {
            int temp = 0;
            for (int matrix_col = 0; matrix_col < col; matrix_col++)
            {
                temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];        
                // matrix_a의 0번째 행과 matrix_t의 0번째 열의 곱들을 더한다. 
                // 다음으로 matrix_a의 1번째 행과 matrix_t의 1번째 열의 곱들을 더한다. (반복...)
                // 이렇게 0번째부터 row-1만큼 행까지 반복한다.
            }
            matrix_axt[matrix_a_row][matrix_t_row] = temp;  
            // 값들을 다 더한 값인 temp를 matrix_axt의 성분에 넣는다. 
            // 이것을 행렬의 열만큼 반복한다. 그러면 한 행씩 채워진다.
        }
    }

    if (matrix_t == NULL || matrix_axt == NULL)     // 만약 matrix_t 또는 matrix_axt가 가리키는 주소가 없을 경우
    {
        printf("Memory Allocation Failed.\n");      // 동적 메모리 할당에 실패했다는 에러메시지 출력
        return -1;
    }

    print_matrix(matrix_axt, row, row);            // matrix_axt의 성분 출력
    free_matrix(matrix_axt, row, col);             // matrix_axt로부터 접근할 수 있는 모든 공간 해제
    return 1;
}