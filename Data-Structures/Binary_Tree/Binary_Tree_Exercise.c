#include <stdio.h>
#include <stdlib.h>

// ===== 이진 트리 노드 구조체 ===== //
typedef struct _btnode {
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

// ===== 스택 구조체 (트리 생성을 위한 보조 도구) ===== //
typedef struct _stackNode {
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack {
    StackNode *top;
} Stack;

// ===== 함수 선언 ===== //
BTNode *createBTNode(int item);
void push(Stack *stk, BTNode *node);
BTNode *pop(Stack *stk);
BTNode *createTree();
void printTree(BTNode *node);
void removeAll(BTNode **node);

// ===== 메인 함수: 메뉴 기반 이진 트리 테스트 ===== //
int main() {
    BTNode *root = NULL;
    int choice = 1;

    printf("===== 이진 트리 실습 프로그램 =====\n");

    while (choice != 0) {
        printf("\n1: 트리 생성\n");
        printf("2: 중위 순회 출력\n");
        printf("3: 트리 메모리 해제\n");
        printf("0: 종료\n");

        printf("메뉴 선택 (0~3): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            removeAll(&root);
            printf("[트리 생성]\n");
            root = createTree();
            break;

        case 2:
            printf("[중위 순회 출력]\n");
            printTree(root);
            printf("\n");
            break;

        case 3:
            printf("[트리 전체 삭제]\n");
            removeAll(&root);
            break;

        case 0:
            removeAll(&root);
            printf("프로그램 종료.\n");
            break;

        default:
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}

// ===== 기본 함수 구현 (힌트 주석 포함) ===== //

// 새로운 트리 노드를 생성하여 반환하는 함수
BTNode *createBTNode(int item) {
    /*  힌트: 메모리 동적 할당 + 값 설정 + 왼쪽/오른쪽 NULL
        add your code here  */
    BTNode *new_node = malloc(sizeof(BTNode));
    new_node->item = item;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// 스택에 노드를 삽입하는 함수
void push(Stack *stk, BTNode *node) {
    /*  힌트: 새로운 StackNode를 만들고 top 앞에 연결
        add your code here  */
    StackNode *new_stack_node = malloc(sizeof(StackNode));
    new_stack_node->btnode = node;
    new_stack_node->next = stk->top;

    stk->top = new_stack_node;
}

// 스택에서 노드를 꺼내고 제거한 뒤 값을 반환하는 함수
BTNode *pop(Stack *stk) {
    /*  힌트: top이 가리키는 StackNode를 제거하고 해당 노드 반환
        add your code here  */
    if (stk->top == NULL) return NULL;

    StackNode *top = stk->top;
    BTNode *node = top->btnode;
    
    stk->top = stk->top->next;
    free(top);

    return node;
}

// 사용자 입력을 통해 이진 트리를 생성하는 함수
BTNode *createTree() {
    Stack stk;
    BTNode *root, *temp;
    char dummy;
    int item;
    
    stk.top = NULL;
    root = NULL;

    printf("루트 노드 값: ");
    if (scanf("%d", &item)) {
        root = createBTNode(item);
        push(&stk, root);
    } else {
        scanf("%c", &dummy);
        return NULL;
    }

    while ((temp = pop(&stk)) != NULL) {
        printf("노드 %d의 왼쪽 자식 노드 값(자식을 만들지 않으려면 아무 문자나 입력): ", temp->item);
        if (scanf("%d", &item)) {
            temp->left = createBTNode(item);
        } else {
            scanf("%c", &dummy);
        }
        printf("노드 %d의 오른쪽 자식 노드 값(자식을 만들지 않으려면 아무 문자나 입력): ", temp->item);
        if (scanf("%d", &item)) {
            temp->right = createBTNode(item);
        } else {
            scanf("%c", &dummy);
        }

        if (temp->right) push(&stk, temp->left);
        if (temp->left) push(&stk, temp->right);
    }

    return root;
}

// 중위 순회로 트리를 출력하는 함수
// 출력 순서: 왼쪽 자식 → 현재 노드 → 오른쪽 자식
void printTree(BTNode *node) {
    if (node == NULL) return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}

// 트리 전체를 삭제하는 함수
void removeAll(BTNode **node) {
    /*  힌트: 후위 순회 방식 - 왼쪽, 오른쪽 먼저 삭제 후 현재 노드 free
        add your code here  */
    if (*node == NULL) return;

    removeAll(&((*node)->left));
    removeAll(&((*node)->right));
    free(*node);
    *node = NULL;
}