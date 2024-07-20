# Cài đặt chương trình
- Ngôn ngữ: Python 3.7
- IDE: Pycharm
- Thư viện cần cài đặt:
    + NumPy 1.17.4
    + SciPy 1.3.2
# Demo chương trình
- Đặt root project là thư mục [**estp**](../estp)
- Chạy file [**main.py**](./main.py) trong thư mục [**estp**](../estp)
# Định dạng input và output
## Input:
- Dòng đầu là số điểm terminal cho trước (N)
- N dòng sau, mỗi dòng là tọa độ 1 điểm, cách nhau bởi khoảng trắng
(Nếu test trên không gian 3 chiều thì mỗi dòng có 3 tọa độ)
    ##### Ví dụ:
        3
        0 0
        0 1
        1 0
## Output:
- Dòng đầu là tổng trọng số cây Steiner nhỏ nhất tìm được
- Dòng hai là số điểm Steiner chèn vào cây (M)
- M dòng sau là tọa độ M điểm Steiner
    ##### Ví dụ:
        1.9318516525781366
        1
        0.2113248654051872 0.2113248654051872
    ##### Lưu ý:
    Nếu các điểm nhập vào có số chiều khác nhau thì báo lỗi.
