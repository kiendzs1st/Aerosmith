# Aerosmith
Họ và tên: Đinh Trung Kiên
Mã sinh viên: 24021538
Thể loại game: Plane Shooter- Điều khiển máy bay bắn kẻ địch
Ngưỡng điểm mong muốn: 9-10
___
#**Tại sao game này xứng đáng với ngưỡng điểm 9-10**
1. Các tính năng:
   -Có hệ thống bắn đạn khi ấn nút
   -Có hệ thống vật phẩm rơi khi kẻ địch bị tiêu diệt:
     +Strength: tăng sát thương khi bắn
     +Speed: tăng tốc độ di chuyển
     +Firing Speed: tăng tốc độ bắn
     +Health: Tăng máu
   -Có hệ thống spawn kẻ địch theo từng wave:
     + Kẻ địch được spawn theo một đội hình nhất định
   -Có hệ thống tăng độ khó theo màn chơi:
     + Sau một số round nhất định, kẻ địch được tăng sức mạnh
   -Kiểm tra va chạm :
     + Sử dụng thuật toán kiểm tra va chạm AABB Collision Detection

   -Có hệ thống điều chỉnh âm thanh:
     + Điều chỉnh âm lượng của nhạc nền
     + Điều chỉnh âm lượng của sound effects
     + Chỉnh nhạc nền
   2. Giao diện và trải nghiệm người dùng:
      - UI đầy đủ:
        + Có Menu chính với các nút Play, Settings, Help và Quit
        + Trong khi chơi game có thể bật Game Menu để restart, vào settings hoặc thoát ra Menu Chính
        + Menu khi chết có restart và trở về menu chính
      - Animation:
        + Các đối tượng trong game đều có animation
        + Animation được vẽ hoàn toàn bằng tay
      - Âm thanh đầy đủ:
        +Có đầy đủ âm thanh khi đang ở màn hình chính hay khi đang chơi game
        +Có đầy đủ sound effects trong gameplay
    3. Quản lý tài nguyên:
       - Khi thoát game, mọi đối tượng trong Game đều được giải phóng, không gây ra memory leak
    4. Chất lượng code:
       -Code có thể dễ dàng thêm các tính năng mới
___
#**Mức độ sử dụng AI**
AI được sử dụng chủ yếu để tra cứu và học về các hàm của SDL2 và được sử dụng để hỗ trợ Debug khi không còn cách nào khác
___
#**Các phần code tham khảo**
[Hàm va chạm](![image](https://github.com/user-attachments/assets/59f5166a-ed1c-4580-b62a-8668ec92bb60)
)
[Tilemap](https://youtu.be/1eaxE_waDNc?si=LS7IJwscN-BuCu9w)
[Texture Management](https://www.youtube.com/watch?v=RqvpkZ7I1aU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=6)
___
# **Các nguồn học**
[Lazyfoo](https://lazyfoo.net/tutorials/SDL/)
[Let's Make Game](https://www.youtube.com/@CarlBirch)
[codergopher](https://www.youtube.com/@codergopher8270)
___
#**Các nguồn tham khảo**
1. Các nguồn âm thanh:
   [Nhạc nền 1](https://youtu.be/U0TXIXTzJEY?si=1Tupd7gzOQQhqCeL)
   [Nhạc nền 2](https://youtu.be/QoHrfKZ5jno?si=0g4zs-rW3eS9G4hk)
   [Nhạc nền 3](https://youtu.be/daFi4MScfl8?si=VuAmxG6SJmfQbaNc)
   [Explosion](https://youtu.be/daFi4MScfl8?si=VuAmxG6SJmfQbaNc)
   [Hit sound effect](https://youtu.be/iyuTagR1u44?si=FJULzoLCFXJpJ2iR)
   [player shooting sound effect](https://youtu.be/FuvmTL1nPDs?si=8bs-oQyU3FLIU0sm)
   [Enemies shooting sound effect](https://youtu.be/jz-awweTKw8?si=BOx02hFAmv3ELEsM)
   [Main menu background music](https://www.youtube.com/watch?v=F6z1CH4oX2o&list=PL0QAEXDsccILdga79CcswY56cxSfLUXY9&index=13)
   [Tiếng ăn vật phẩm](https://youtu.be/uTg0i6j7k34?si=nkSlcO_52h_jfpGp)

2. Các nguồn hình ảnh
   [Background Menu Chính](https://za.pinterest.com/pin/54395107993157287/)
   [Background GameOver]()
   

       
