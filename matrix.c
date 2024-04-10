#include <stdio.h> // 표준입출력 라이브러리 사용하기 위한 라이브러리 불러오기
#include <stdlib.h> // 동적 메모리 할당 및 해제 함수를 사용하기 위한 라이브러리 불러오기
#include <time.h> // 난수 생성을 위한 라이브러리 불러오기

void print_matrix(int**matrix_a,int**matrix_b, int**result_matrix, char flag); // 두 개의 행렬과 그 결과 행렬을 출력하는 함수를 선언 (flag 매개변수는 어떤 연산을 나타내는지 표시)
void addition_matrix(int**matrix_a, int**matrix_b); // 행렬 A,B를 더하는 함수를 선언
void subtraction_matrix(int**matrix_a, int**matrix_b); // 행렬 A,B를 빼는 함수를 선언
void transpose_matrix(int**matrix_a, int**matrix_b); // 행렬 A를 전치하는 함수를 선언
void multiply_matrix(int**matrix_a, int**matrix_b);// 행렬 A,B를 곱하는 함수를 선언
void free_matrix(int **matrix, int state); // 동적으로 할당된 메모리를 해제하는 함수를 선언 (state 매개변수는 전치 행렬인지 아닌지 구분)

int row, column; // 행렬의 행,열을 저장하기 위한 정수형 전역 변수 row, column 선언

int main(void){
    printf("[----- [Goh Geon Young]  [2020017027] -----]\n");
    srand(time(NULL)); // 난수 생성 시 초기 시드 값을 설정 -> 매번 다른 시드값 생성

    /* Input 행, 열 값 받기 */
    printf("[A&B] row column: ");
    scanf("%d %d",&row,&column); // input으로 받은 값을 정수형 변수 row, column의 주소안에 값 저장

    /* matrix 동적 할당*/
    /* 2차원 배열을 동적 할당을 할 때 
    행에 대해 먼저 동적 할당을 하고 그 다음에 열을 채워야한다. */
    int**matrix_a = (int**)malloc(sizeof(int*) * row); // 행렬 A의 행에 대한 동적 할당 ((8 * row)bytes)크기만큼 먼저 할당.
    int**matrix_b = (int**)malloc(sizeof(int*) * row); // 행렬 B의 행에 대한 동적 할당 ((8 * row)bytes)크기만큼 먼저 할당.
    for (int i = 0 ; i < row; i++){
        matrix_a[i] = (int*)malloc(sizeof(int)*column); // 행렬 A의 열에 대한 동적 할당 (위에 행의 공간안에 ((4 * column)bytes)크기를 할당 한다.)
        matrix_b[i] = (int*)malloc(sizeof(int)*column); // 행렬 B의 열에 대한 동적 할당 (위에 행의 공간안에 ((4 * column)bytes)크기를 할당 한다.)
    }

    /* 행렬에 랜덤한 난수 값 할당 */
    for (int i = 0; i< row; i++){
        for(int j = 0; j<column;j++){
            matrix_a[i][j] = rand()%9;  // 0~8 사이의 값을 행렬 A[i][j]에 할당
            matrix_b[i][j] = rand()%9;  // 0~8 사이의 값을 행렬 B[i][j]에 할당
        }
    }
    
    /* 행렬 A + B  구현 및 출력 */
    addition_matrix(matrix_a, matrix_b);

    /* 행렬 A - B  구현 및 출력 */
    subtraction_matrix(matrix_a, matrix_b);

    /* A행렬의 전치 행렬 구현 및 출력 */
    transpose_matrix(matrix_a, matrix_b);

    /* 행렬 A X B  구현 및 출력 */
    multiply_matrix(matrix_a, matrix_b);

    
    /* 행렬 A, 행렬 B 동적 할당 해제 */
    free_matrix(matrix_a,0);
    free_matrix(matrix_b,0);

    return 0; // 0 반환 및 프로그램 종료
}

void output(int**matrix){
    /* 행렬 matrix의 모든 요소를 출력하는 함수 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            printf("%d ",matrix[i][j]); // row, column을 이용하여 2중 for문으로 매개변수로 받은 행렬의 모든 요소를 출력한다.
        }
        printf("\n");
    }
}

int** make_result_matrix(int**matrix){
    /* 연산 결과를 저장하는 행렬인 result_matrix의 동적 할당을 하는 함수 */
    matrix = (int**)malloc(sizeof(int*) * row); // 매개변수로 받은 행렬 matrix의 행에 대한 동적 할당 ((8 * row)bytes)크기만큼 먼저 할당.
    for (int i = 0 ; i < row; i++){
        matrix[i] = (int*)malloc(sizeof(int)*column); // 매개변수로 받은 행렬 matrix의 열에 대한 동적 할당 (위에 행의 공간안에 ((4 * column)bytes)크기를 할당 한다.)
    }
    return matrix; // 동적 할당이 된 matrix를 반환한다.
}

void print_matrix(int**matrix_a,int**matrix_b, int**result_matrix, char flag){
    /* 연산 시 결과를 출력하는 함수 */
    printf("[MATRIX A]\n");
    output(matrix_a); // 행렬 A의 모든 요소를 출력
    printf("================================\n");

    printf("[MATRIX B]\n");
    output(matrix_b); // 행렬 B의 모든 요소를 출력
    printf("================================\n");

    switch(flag){ // 매개변수 flag에 따라 출력이 다름.
        case '+': // 더하기 연산일 때 
            printf("[MATRIX A + MATRIX B]\n");
            output(result_matrix); // 매개변수로 받은 result_matrix의 모든 요소를 출력
            break;
        case '-': // 빼기 연산일 때 
            printf("[MATRIX A - MATRIX B]\n");
            output(result_matrix); // 매개변수로 받은 result_matrix의 모든 요소를 출력
            break;
        case 'X': // 곱하기 연산일 때 
            printf("[MATRIX A X MATRIX B]\n");
            output(result_matrix); // 매개변수로 받은 result_matrix의 모든 요소를 출력
            break;
        case 'T': // 전치일 때
            printf("[TRANSPOSE MATRIX A]\n");
            // 전치 행렬은 row, column이 기존과 반대이기 때문에 따로 구현
            for (int i = 0; i<column; i++){
                for (int j = 0; j<row; j++){
                    printf("%d ",result_matrix[i][j]); // row, column을 이용하여 2중 for문으로 매개변수로 받은 result_matrix 행렬의 모든 요소를 출력한다.
                }
                printf("\n");
            }
            break;
    }
    printf("\n=============================[END]=============================\n");
}

void free_matrix(int **matrix, int state){
    /* 매개변수로 받은 행렬의 동적할당을 해제하는 함수 */
    /* Transpose일 땐 column의 숫자별로 할당을 해제해야 해서 매개변수로 상태(state)값을 받는다. */
    int num;
    if (state != 1){
        num = row; // 나머지 경우 (행의 수가 row이기 때문)
    }else{ 
        num = column; // Transpose일 때 (행의 수가 column이기 때문)
    }

    for (int i=0; i<num;i++){
        free(matrix[i]); // 각 행 동적할당된 메모리 해제
    }
    free(matrix); // 메모리 heap 공간에 동적할당된 메모리 해제
}

void addition_matrix(int**matrix_a, int**matrix_b){
    /* 행렬 A와 B를 더하는 함수 */
    int**result_matrix; // 결과를 저장할 result_matrix 선언
    result_matrix = make_result_matrix(result_matrix); // result_matrix에 동적 할당

    /* 행렬 A와 B 더한 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j]; // 행렬 A와 B를 각각 더한 값을 결과 저장 행렬 result_matrix에 저장
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'+');

    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,0);
}

void subtraction_matrix(int**matrix_a, int**matrix_b){
    /* 행렬 A와 B를 빼는 함수 */
    int**result_matrix; // 결과를 저장할 result_matrix 선언
    result_matrix = make_result_matrix(result_matrix); // result_matrix에 동적 할당
    /* 행렬 A와 B 뺀 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j]; // 행렬 A와 B를 각각 뺀 값을 결과 저장 행렬 result_matrix에 저장
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'-');
    
    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,0);
}

void multiply_matrix(int**matrix_a, int**matrix_b){
    /* 행렬 A와 B를 곱하는 함수 */
    int**result_matrix; // 결과를 저장할 result_matrix 선언
    result_matrix = make_result_matrix(result_matrix); // result_matrix에 동적 할당

    /* 행렬 A와 B 곱한 값 result_matrix에 저장 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[i][j] = matrix_a[i][j] * matrix_b[i][j]; // 행렬 A와 B를 각각 곱한 값을 결과 저장 행렬 result_matrix에 저장
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

    /* 행렬 A의 전치 행렬 생성 */
    for (int i = 0; i<row; i++){
        for (int j = 0; j<column; j++){
            result_matrix[j][i] = matrix_a[i][j]; // i,j를 반대로 저장하면서 행렬 A의 전치 행렬 생성
        }
    }
    /* 결과값 프린트 */
    print_matrix(matrix_a,matrix_b,result_matrix,'T');

    /* result_matrix 동적 할당 해제 */
    free_matrix(result_matrix,1); // 전치 행렬의 해제이기 때문에 1을 전달
}