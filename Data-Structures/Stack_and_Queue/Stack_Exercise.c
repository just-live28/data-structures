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
// 스택 구조체
typedef struct _stack
{
	LinkedList ll;
}Stack;

// 기본 함수 선언
void push(Stack *s , int item);
int isEmptyStack(Stack *s);
int pop(Stack *s);
void removeAllItemsFromStack(Stack *s);

ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);

// 스택 기본 함수 확인용 프로그램
// 함수 구현 후 C파일을 실행해 제대로 동작하는지 테스트해볼 수 있습니다.
int main() {
    Stack s;
	s.ll.head = NULL;
	s.ll.size = 0;

	int c = 1;
	int value, result;

    printf("===== 스택 테스트 메뉴 =====\n");
    printf("1: push(value)\n");
    printf("2: pop()\n");
    printf("3: isEmptyStack()\n");
    printf("4: printList()\n");
    printf("5: removeAllItemsFromStack()\n");
    printf("0: 종료\n");

	while (c != 0) {
		printf("\n메뉴 선택 (0~5): ");
		scanf("%d", &c);

		switch (c) {
		case 1:
			printf("삽입할 값을 입력하세요: ");
			scanf("%d", &value);
			push(&s, value);
			printf("삽입 성공!\n");
			printList(&(s.ll));
			break;

		case 2:
			result = pop(&s);
			if (result != -1)
				printf("꺼낸 값: %d\n", result);
			else
				printf("스택이 비어 있습니다.\n");
			printList(&(s.ll));
			break;

		case 3:
			if (isEmptyStack(&s))
				printf("스택은 비어 있습니다.\n");
			else
				printf("스택에 값이 존재합니다.\n");
			break;

		case 4:
            printf("스택(앞쪽이 top): ");
			printList(&(s.ll));
			break;

		case 5:
			removeAllItemsFromStack(&s);
			printf("모든 요소 제거 완료!\n");
			printList(&(s.ll));
			break;

		case 0:
			removeAllItemsFromStack(&s);
			printf("프로그램 종료.\n");
			break;

		default:
			printf("알 수 없는 선택입니다.\n");
			break;
		}
	}

	return 0;
}

// 스택 최상단에 요소를 삽입하는 함수
void push(Stack *s, int item)
{
    // 연결 리스트의 head 위치(=맨 앞)에 노드를 삽입
    insertNode(&(s->ll), 0, item);
}

// 스택이 비었는지 확인하는 함수
// 스택이 비어있으면 1, 아니면 0을 반환
int isEmptyStack(Stack *s)
{
    if (s->ll.size == 0) {
        return 1;
    }
    return 0;
}

// 스택 최상단에서 요소를 꺼내고 제거하는 함수
// 스택이 비어있으면 -1, 아니면 꺼낸 값을 반환
int pop(Stack *s)
{
    if (isEmptyStack(s)) return -1;     // 비어 있으면 -1 반환

    int val = s->ll.head->item;         // 맨 앞 노드의 값 꺼내기
    removeNode(&(s->ll), 0);            // index 0 위치 제거
    return val;                         // 꺼낸 값 반환
}

// 스택의 모든 요소를 제거하는 함수
void removeAllItemsFromStack(Stack *s) {   
    // 이미 비어 있다면 return
    if (isEmptyStack(s)) return;
    // 스택이 빌 때까지 pop 반복
    while (!isEmptyStack(s)) pop(s);
}

// ==================== 기존 연결 리스트 기본 함수 ==================== //
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