#include <stdio.h>
#include <stdlib.h>

// 연결 리스트 구조체
typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;
// 노드 구조체
typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;

// 기본 함수 선언
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);

// 연결 리스트 기본 함수 확인용 프로그램
// 함수 구현 후 C파일을 실행해 제대로 동작하는지 테스트해볼 수 있습니다.
int main() {
    LinkedList ll;
    int c = 1;
    int index, value;
    ListNode *node;

    // 초기화
    ll.head = NULL;
    ll.size = 0;

    printf("===== 연결 리스트 테스트 메뉴 =====\n");
    printf("1: insertNode(index, value)\n");
    printf("2: removeNode(index)\n");
    printf("3: findNode(index)\n");
    printf("4: printList()\n");
    printf("5: removeAllItems()\n");
    printf("0: 종료\n");

    while (c != 0) {
        printf("\n메뉴 선택 (0~5): ");
        scanf("%d", &c);

        switch (c) {
        case 1:
            printf("삽입할 인덱스를 입력하세요: ");
            scanf("%d", &index);
            printf("삽입할 값을 입력하세요: ");
            scanf("%d", &value);
            if (insertNode(&ll, index, value) == 0) {
                printf("삽입 성공!\n");
                printf("현재 연결 리스트: ");
                printList(&ll);
            } else
                printf("삽입 실패 (인덱스 오류)!\n");
            break;
        case 2:
            printf("삭제할 인덱스를 입력하세요: ");
            scanf("%d", &index);
            if (removeNode(&ll, index) == 0) {
                printf("삭제 성공!\n");
                printf("현재 연결 리스트: ");
                printList(&ll);
            } else
                printf("삭제 실패 (인덱스 오류)!\n");
            break;
        case 3:
            printf("찾을 인덱스를 입력하세요: ");
            scanf("%d", &index);
            node = findNode(&ll, index);
            if (node != NULL)
                printf("해당 노드의 값: %d\n", node->item);
            else
                printf("노드를 찾을 수 없습니다 (인덱스 오류)!\n");
            break;

        case 4:
            printf("현재 연결 리스트: ");
            printList(&ll);
            break;

        case 5:
            removeAllItems(&ll);
            printf("모든 노드 삭제 완료!\n");
            break;

        case 0:
            removeAllItems(&ll);
            printf("프로그램 종료.\n");
            break;

        default:
            printf("알 수 없는 선택입니다.\n");
            break;
        }
    }
    
    return 0;
}

// index에 해당하는 노드의 주소를 반환하는 함수
// 노드를 찾았다면 해당 노드, 노드를 찾을 수 없다면 NULL 반환
ListNode *findNode(LinkedList *ll, int index)
{
    if (ll == NULL || ll->head == NULL || index < 0 || index >= ll->size) return NULL;

    ListNode *cur = ll->head;
    int i = 0;
    while (i < index) {
        cur = cur->next;
        i++;
    }
    return cur;
}

// index 위치에 새로운 노드를 삽입하는 함수
// 성공 시 0, 실패 시 -1 반환
int insertNode(LinkedList *ll, int index, int value)
{
    if (index < 0 || index > ll->size) return -1;

    ListNode *pre;
    ListNode *new_node = malloc(sizeof(ListNode));
    new_node->item = value;
    new_node->next = NULL;
    if (index == 0) {
        new_node->next = ll->head;
        ll->head = new_node;
    } else {
        pre = findNode(ll, index -1);
        new_node->next = pre->next;
        pre->next = new_node;
    }

    ll->size++;
    return 0;
}

// index 위치의 노드를 삭제하는 함수
// 성공 시 0, 실패 시 -1 반환
int removeNode(LinkedList *ll, int index)
{
    if (ll == NULL || ll->head == NULL || index < 0 || index >= ll->size) return -1;

    ListNode *pre, *cur;
    if (index == 0) {
        cur = ll->head;
        ll->head = cur->next;
        free(cur);
    } else {
        pre = findNode(ll, index-1);
        cur = pre->next;
        
        pre->next = cur->next;
        free(cur);
    }

    ll->size--;
    return 0;
}

// 연결 리스트의 모든 노드 값을 순서대로 출력하는 함수
void printList(LinkedList *ll)
{
    ListNode *cur;
    printf("현재 연결 리스트: ");
    if (ll == NULL || ll->head == NULL) {
        printf("Empty\n");
    } else {
        cur = ll->head;
        while (cur != NULL) {
            printf("%d ", cur->item);
            cur = cur->next;
        }
        printf("\n");
    }
}

// 연결 리스트의 모든 노드를 제거하고 초기화하는 함수
void removeAllItems(LinkedList *ll)
{
    if (ll == NULL || ll->head == NULL) {
        return;
    }

    ListNode *cur;
    while (ll->head != NULL) {
        cur = ll->head;
        ll->head = cur->next;
        free(cur);
        ll->size--;
    }
    printf("리스트 초기화 완료\n");
}