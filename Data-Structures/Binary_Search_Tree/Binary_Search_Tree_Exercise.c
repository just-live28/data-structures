//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

///////////////////////////////////////////////////////////////////////////////////

// 삽입
void insertBSTNode(BSTNode **node, int value);
// 탐색
BSTNode* searchBSTNode(BSTNode *node, int value);
// 삭제
void deleteBSTNode(BSTNode **node, int value);
// 전체 트리 메모리 해제
void removeAll(BSTNode **node);

/////////////////// 이진 탐색 트리 테스트 프로그램 ///////////////////

int main()
{
	int c, i;
	c = 1;

	BSTNode *root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Search for a value in the binary search tree;\n");
	printf("3: Delete a value from the binary search tree;\n");
	printf("4: Remove the entire binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("\nPlease input your choice(0~4): ");
		scanf("%d", &c);

		switch (c)
        {
            case 1:
                printf("Input an integer to insert: ");
                scanf("%d", &i);
                insertBSTNode(&root, i);
                break;

            case 2:
                printf("Input an integer to search: ");
                scanf("%d", &i);
                BSTNode *found = searchBSTNode(root, i);
                if (found != NULL)
                    printf("Found node with value %d.\n", found->item);
                else
                    printf("Value not found.\n");
                break;

            case 3:
                printf("Input an integer to delete: ");
                scanf("%d", &i);
                deleteBSTNode(&root, i);
                break;

            case 4:
                removeAll(&root);
                printf("All nodes removed. Tree is now empty.\n");
                break;

            case 0:
                removeAll(&root);  // 종료 전에도 안전하게 메모리 해제
                break;

            default:
                printf("Unknown choice.\n");
                break;
        }

	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
    // TODO: 이진 탐색 트리 삽입 로직 구현
    // - 현재 노드가 NULL이면 새 노드를 생성해 연결
    // - 값이 작으면 왼쪽 서브트리로, 크면 오른쪽 서브트리로 재귀 호출
}

BSTNode* searchBSTNode(BSTNode *node, int value) {
    // TODO: 재귀 또는 반복으로 value를 가진 노드를 찾아 반환
    // 찾으면 해당 노드 포인터 반환
    // 없으면 NULL 반환
}

void deleteBSTNode(BSTNode **node, int value) {
    // TODO: 이진 탐색 트리 삭제 로직 구현
    // 세 가지 경우를 고려
    // - 자식이 없는 노드
    // - 자식이 하나 있는 노드
    // - 자식이 두 개인 노드 (inorder successor 또는 predecessor 사용)
}

void removeAll(BSTNode **node) {
    // TODO: 트리 전체를 후위 순회(post-order traversal) 방식으로 해제
}

//////////////////////////////////////////////////////////////////////////////////