# 입력부
import sys

input = sys.stdin.readline
INF = 1e9

N, M, K = map(int, input().split())  # 미로 크기, 참가자 수, 게임시간
array = [list(map(int, input().split())) for _ in range(N)]  # 격자
peoples = []  # 참가자들
for _ in range(M):
    a, b = map(int, input().split())
    peoples.append((a - 1, b - 1))
a, b = map(int, input().split())  # 출구
exit_x, exit_y = a - 1, b - 1
# array[exit_x][exit_y] = -1                                      # 출구 -1로 정하기
total_movement = 0  # 모든 참가자 이동거리 합

dx = [-1, 1, 0, 0]  # 상하좌우
dy = [0, 0, -1, 1]


# 함수부
# 정사각형 만드는 함수
def make_square(cordinate1, cordinate2):
    x1, y1, x2, y2 = cordinate1[0], cordinate1[1], cordinate2[0], cordinate2[1]
    square_size = max(abs(x1 - x2) + 1, abs(y1 - y2) + 1)
    for i in range(N):
        start_x, end_x = i, i + square_size - 1
        if (end_x < N) and (start_x <= x1 <= end_x) and (start_x <= x2 <= end_x):
            for j in range(N):
                start_y, end_y = j, j + square_size - 1
                if (end_y < N) and (start_y <= y1 <= end_y) and (start_y <= y2 <= end_y):
                    return (start_x, start_y, square_size, end_x, end_y)
    return (0, 0, INF)


# 수행부
for _ in range(K):

    # 사람들 이동하기
    new_people = []  # 탈출하지 못한 사람들 리스트
    for person in peoples:
        person_x, person_y = person[0], person[1]
        curent_shortcut = abs(person_x - exit_x) + abs(person_y - exit_y)  # 현재에서 출구까지 최단거리
        for i in range(4):
            nx, ny = person_x + dx[i], person_y + dy[i]
            new_shortcut = abs(nx - exit_x) + abs(ny - exit_y)  # 새로 이동한 곳에서 출구까지 최단거리
            if (new_shortcut < curent_shortcut) and (0 <= nx < N) and (0 <= ny < N) and array[nx][ny] == 0:
                total_movement += 1
                person_x, person_y = nx, ny
                break
        if (person_x, person_y) != (exit_x, exit_y):  # 출구에 도달하지 못했다면
            new_people.append([person_x, person_y])

    peoples = new_people.copy()
    # print(exit_x, exit_y)
    # print("move_after", peoples)

    # 모두 탈출에 성공했다면 종료
    if len(peoples) == 0:
        break

    # 정사각형 만들기
    # 가장 작은 정사각형을 만든다면 사람과 출구는 무조건 꼭짓점에 위치한다.
    squares = []
    for person in peoples:
        # print("squre_make", exit_x, exit_y, person[0], person[1])
        squares.append(make_square((exit_x, exit_y), (person[0], person[1])))

    squares = sorted(squares, key=lambda x: (x[2], x[0], x[1]))
    # print(squares)


    # 정사각형 회전하기 -> 나중에 디버깅할때 살펴보기
    (square_start_x, square_start_y, square_size, square_end_x, square_end_y) = squares[0]

    # print(square_start_x, square_start_y, square_size, square_end_x, square_end_y)

    tmp_array = [[0 for _ in range(N)] for _ in range(N)]
    for i in range(square_start_x, square_start_x + square_size):
        for j in range(square_start_y, square_start_y + square_size):
            ox, oy = i - square_start_x,  j - square_start_y   # 위치 변환
            rx, ry = oy, square_size - ox - 1
            tmp_array[rx + square_start_x][ry + square_start_y] = array[i][j]
            if tmp_array[rx + square_start_x][ry + square_start_y] > 0:
                tmp_array[rx + square_start_x][ry + square_start_y] -= 1  # 정사각형 내구도 깎기

    for i in range(square_start_x, square_start_x + square_size):
        for j in range(square_start_y, square_start_y + square_size):
            array[i][j] = tmp_array[i][j]

    # 출구 회전하기
    # print()
    # print(exit_x, exit_y)
    # print(square_start_x, square_start_y, square_size)
    if (square_start_x <= exit_x < square_start_x + square_size) and (square_start_y <= exit_y < square_start_y + square_size):
        ox, oy = exit_x - square_start_x, exit_y - square_start_y
        rx, ry = oy, square_size - ox - 1
        exits = (rx + square_start_x, ry + square_start_y)
    exit_x, exit_y = square_start_x + rx, square_start_y +ry
    # print(exit_x, exit_y)
    # print()

    # print(square_start_x, square_start_y, square_size, square_end_x, square_end_y)
    # 사람 회전하기
    for i in range(len(peoples)):
        if (square_start_x <= peoples[i][0] <= square_end_x) and (square_start_y <= peoples[i][1] <= square_end_y):
            ox, oy = peoples[i][0] - square_start_x, peoples[i][1] - square_start_y
            rx, ry = oy, square_size - ox - 1
            peoples[i][0], peoples[i][1] =(rx + square_start_x, ry + square_start_y)
    # print(peoples)

#     # 확인용
#     for i in range(N):
#         for j in range(N):
#             print(array[i][j], end=' ')
#         print()
#     print()

print(total_movement)
print(exit_x + 1, exit_y + 1)
