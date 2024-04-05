#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

void print_matrix(int**matrix_a,int**matrix_b, int**result_matrix, char flag);
void addition_matrix(int**matrix_a, int**matrix_b);
void subtraction_matrix(int**matrix_a, int**matrix_b);
void transpose_matrix(int**matrix_a, int**matrix_b);
void multiply_matrix(int**matrix_a, int**matrix_b);
void free_matrix();

int row, column; // row, column global 변수 선언

int main(void){
    printf("[----- [Goh Geon Young]  [2020017027] -----]\n");
    srand(time(NULL)); // 난수 생성 시 초기 시드 값을 설정 -> 매번 다른 시드값 생성
    // int row, column;
    /* Input 받기 */
    printf("[A&B] row column: ");
    scanf("%d %d",&row,&column);

    /* matrix 동적 할당*/
    int**matrix_a = (int**)malloc(sizeof(int*) * row); // 행렬 A의 행에 대한 동적 할당
    int**matrix_b = (int**)malloc(sizeof(int*) * row); // 행렬 B의 행에 대한 동적 할당

    for (int i = 0 ; i < row; i++){
        matrix_a[i] = (int*)malloc(sizeof(int)*column); // 행렬 A의 열에 대한 동적 할당
        matrix_b[i] = (int*)malloc(sizeof(int)*column); // 행렬 B의 열에 대한 동적 할당
    }
    /* 행렬에 랜덤한 난수 값 할당 */
    for (int i = 0; i< row; i++){
        for(int j = 0; j<column;j++){
            matrix_a[i][j] = rand()%9;  // 0~8 사이의 값 할당
            matrix_b[i][j] = rand()%9;  // 0~8 사이의 값 할당
        }
    }
    /* 행렬 A + B  구현 및 출력*/
    addition_matrix(matrix_a, matrix_b);
    /* 행렬 A - B  구현 및 출력*/
    subtraction_matrix(matrix_a, matrix_b);
    /* 행렬 A행렬의 전치 행렬 구현 및 출력*/
    transpose_matrix(matrix_a, matrix_b);
    /* 행렬 A X B  구현 및 출력*/
    multiply_matrix(matrix_a, matrix_b);

    
    /* result_matrix 동적 할당 해제 */
    free_matrix(matrix_a,0);
    free_matrix(matrix_b,0);
    return 0;
}

void output(int**matrix){
    /* matrix output을 출력하는 함수 생성 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

int** make_result_matrix(int**matrix){
    /* result matrix 동적 할당 함수 생성 */
    matrix = (int**)malloc(sizeof(int*) * row); // 행렬 matrix의 행에 대한 동적 할당
    for (int i = 0 ; i < row; i++){
        matrix[i] = (int*)malloc(sizeof(int)*column); // 행렬 matrix의 열에 대한 동적 할당
    }
    return matrix;
}

void print_matrix(int**matrix_a,int**matrix_b, int**result_matrix, char flag){
    
    printf("[MATRIX A]\n");
    output(matrix_a);
    printf("================================\n");

    printf("[MATRIX B]\n");
    output(matrix_b);
    printf("================================\n");

    switch(flag){
        case '+':
            printf("[MATRIX A + MATRIX B]\n");
            output(result_matrix);
            break;
        case '-':
            printf("[MATRIX A - MATRIX B]\n");
            output(result_matrix);
            break;
        case 'X':
            printf("[MATRIX A X MATRIX B]\n");
            output(result_matrix);
            break;
        case 'T':
            printf("[TRANSPOSE MATRIX A]\n");
            for (int i = 0; i<column; i++){
                for (int j = 0; j<row; j++){
                    printf("%d ",result_matrix[i][j]);
                }
                printf("\n");
            }
            break;
    }
    printf("\n=============================[END]=============================\n");
}

void free_matrix(int **matrix, int state){
    // 매개변수로 받은 행렬의 동적할당을 해제하는 함수
    /* Transpose일 땐 column의 숫자 별로 할당을 해제해야 해서 매개변수로 상태(state)값을 받는다. */
    int num;
    if (state != 1){
        num = row; // 나머지 경우
    }else{ 
        num = column; // Transpose일 때
    }

    for (int i=0; i<num;i++){
        free(matrix[i]); // 각 행 동적할당된 메모리 해제
    }
    free(matrix); // 메모리 heap 공간에 동적할당된 메모리 해제
}

void addition_matrix(int**matrix_a, int**matrix_b){
    /* output_matrix 동적 할당*/
    int**result_matrix;
    result_matrix = make_result_matrix(result_matrix);
    /* 행렬 A와 B 더한 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'+');

    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,0);
}

void subtraction_matrix(int**matrix_a, int**matrix_b){
    /* output_matrix 동적 할당*/
    int**result_matrix;
    result_matrix = make_result_matrix(result_matrix);
    /* 행렬 A와 B 뺀 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'-');
    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,0);
}

void multiply_matrix(int**matrix_a, int**matrix_b){
    /* output_matrix 동적 할당*/
    int**result_matrix;
    result_matrix = make_result_matrix(result_matrix);
    /* 행렬 A와 B 곱한 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[i][j] = matrix_a[i][j] * matrix_b[i][j];
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'X');
    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,0);
}

void transpose_matrix(int**matrix_a, int**matrix_b){
    /* result matrix 동적 할당 함수 생성 */
    int**result_matrix = (int**)malloc(sizeof(int*) * column); // 행렬 result_matrix의 행에 대한 동적 할당
    for (int i = 0 ; i < column; i++){
        result_matrix[i] = (int*)malloc(sizeof(int)*row); // 행렬 result_matrix의 열에 대한 동적 할당
    }

    /* 행렬 A와 B 곱한 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            // printf("%d",result_matrix[j][i]);
            result_matrix[j][i] = matrix_a[i][j];
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'T');
    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,1);
}