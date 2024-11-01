/*
Cho dãy số nguyên A: A1,A2,...,An
Dãy hoán vị P: P1,P2,...,Pn của n số 1,2,...,n.
Thực hiện q truy vấn số từ 1 đến q, mỗi truy vấn thuộc một trong các loại sau:
1 l r v : gán A_Pi = A_Pi + v với i thuộc [l,r]
2 l r : tính tổng A_l + A_{l+1} + ... + A_r
3 x y : đổi chỗ Px và Py
4 t : giá trị của dãy A và P quay trở lại trước truy vấn thứ t.
Bạn sẽ cần đưa ra kết quả đối với mỗi truy vấn loại 2.
Input:
- Dòng đầu chứa hai số nguyên n,q ( 1 <= n, q <= 150,000)
- Dòng thứ hai chứa dãy số nguyên Ai ( 0 <= A_i <= 10^9)
- Dòng thứ ba chứa dãy hoán vị Pi (1 <= Pi <= Pn)
- Dòng thứ s trong số q dòng tiếp theo mô tả một trong bốn loại truy
vấn nêu trên 
(
1 <= l <= r <= n
0 <= v <= 10^5
1 <= x,y <= n
1 <= t <= s
)
Các số trên một dòng cách nhau bởi dấu cách.
Output:
Với mỗi truy vấn loại 2 ghi ra thiết bị ra chuẩn giá trị tính được trên một dòng.
*/
#include <iostream>
#include <vector>
#include <cassert>

class QueryHandler {
private:
    std::vector<long long> A;  // Dãy số A
    std::vector<int> P;        // Dãy hoán vị P
    std::vector<std::pair<std::vector<long long>, std::vector<int>>> history; // Lịch sử trạng thái

public:
    QueryHandler(const std::vector<long long>& a, const std::vector<int>& p) : A(a), P(p) {
        // Lưu trạng thái đầu tiên vào lịch sử
        history.emplace_back(A, P);
    }

    void update(const int l, const int r, const long long v) {
        for (int i = l; i <= r; i++) {
            A[P[i] - 1] += v; // Cập nhật theo hoán vị
        }
        // Lưu trạng thái mới vào lịch sử
        history.emplace_back(A, P);
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    long long querySum(const int l, const int r) {
        long long total = 0;
        for (int i = l; i <= r; i++) {
            total += A[P[i] - 1];
        }
        return total;
    }

    void swapPositions(int x, int y) {
        std::swap(P[x], P[y]);
        // Lưu trạng thái mới vào lịch sử
        history.emplace_back(A, P);
    }

    void revert(int t) {
        // Quay lại trạng thái trước truy vấn thứ t
    assert(t < static_cast<int>(history.size())); // Đảm bảo t hợp lệ
        A = history[t].first;
        P = history[t].second;
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;

    // Nhập dãy số nguyên A
    std::vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    // Nhập dãy hoán vị P
    std::vector<int> P(n);
    for (int i = 0; i < n; i++) {
        std::cin >> P[i];
    }

    // Xử lý các truy vấn
    std::vector<long long> result;
    QueryHandler handler(A, P);
    for (int index = 0; index < q; index++) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int l, r;
            long long v;
            std::cin >> l >> r >> v;
            handler.update(l - 1, r - 1, v); // Chỉ số bắt đầu từ 0
        }
        else if (type == 2) {
            int l, r;
            std::cin >> l >> r;
            result.push_back(handler.querySum(l - 1, r - 1));
        }
        else if (type == 3) {
            int x, y;
            std::cin >> x >> y;
            handler.swapPositions(x - 1, y - 1);
        }
        else if (type == 4) {
            int t;
            std::cin >> t;
            handler.revert(t - 1);
        }
    }

    // In kết quả của các truy vấn loại 2
    for (const long long i : result) {
        std::cout << i << std::endl;
    }

    return 0;
}
