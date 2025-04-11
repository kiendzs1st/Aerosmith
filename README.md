# Aerosmith
Họ và tên: Đinh Trung Kiên
Mã sinh viên: 24021538
Thể loại game: Plane Shooter- Điều khiển máy bay bắn kẻ địch
Ngưỡng điểm mong muốn: 9-10
___
#**Tại sao game này xứng đáng với ngưỡng điểm 9-10**
1. Các tính năng:<br>
   -Có hệ thống bắn đạn khi ấn nút
   -Có hệ thống vật phẩm rơi khi kẻ địch bị tiêu diệt:<br>
     +Strength: tăng sát thương khi bắn<br>
     +Speed: tăng tốc độ di chuyển<br>
     +Firing Speed: tăng tốc độ bắn<br>
     +Health: Tăng máu<br>
   -Có hệ thống spawn kẻ địch theo từng wave:<br>
     + Kẻ địch được spawn theo một đội hình nhất định<br>
   -Có hệ thống tăng độ khó theo màn chơi:<br>
     + Sau một số round nhất định, kẻ địch được tăng sức mạnh<br>
   -Kiểm tra va chạm :<br>
     + Sử dụng thuật toán kiểm tra va chạm AABB Collision Detection<br>
   -Có hệ thống điều chỉnh âm thanh:<br>
     + Điều chỉnh âm lượng của nhạc nền<br>
     + Điều chỉnh âm lượng của sound effects<br>
     + Chỉnh nhạc nền<br>
   2. Giao diện và trải nghiệm người dùng:<br>
      - UI đầy đủ:<br>
        + Có Menu chính với các nút Play, Settings, Help và Quit<br>
        + Trong khi chơi game có thể bật Game Menu để restart, vào settings hoặc thoát ra Menu Chính<br>
        + Menu khi chết có restart và trở về menu chính<br>
      - Animation:<br>
        + Các đối tượng trong game đều có animation<br>
        + Animation được vẽ hoàn toàn bằng tay<br>
      - Âm thanh đầy đủ:<br>
        +Có đầy đủ âm thanh khi đang ở màn hình chính hay khi đang chơi game<br>
        +Có đầy đủ sound effects trong gameplay<br>
    3. Quản lý tài nguyên:<br>
       - Khi thoát game, mọi đối tượng trong Game đều được giải phóng, không gây ra memory leak<br>
    4. Chất lượng code:<br>
       -Code có thể dễ dàng thêm các tính năng mới<br>
___
#**Mức độ sử dụng AI**
Mọi thứ trong game đều được tự code hoặc đi tham khảo video và document trên mạng.AI được sử dụng chủ yếu để tra cứu và học về các hàm của SDL2, vẽ background của GameOver và được sử dụng để hỗ trợ Debug khi không còn cách nào khác
___
#**Các phần code tham khảo**<br>
[Hàm va chạm](https://lazyfoo.net/tutorials/SDL/)<br>
[Tilemap](https://youtu.be/1eaxE_waDNc?si=LS7IJwscN-BuCu9w)<br>
[Texture Management](https://www.youtube.com/watch?v=RqvpkZ7I1aU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=6)<br>
___
# **Các nguồn học**<br>
[Lazyfoo](https://lazyfoo.net/tutorials/SDL/)<br>
[Let's Make Game](https://www.youtube.com/@CarlBirch)<br>
[codergopher](https://www.youtube.com/@codergopher8270)<br>
___
#**Các nguồn tham khảo**
1. Các nguồn âm thanh:<br>
   [Nhạc nền 1](https://youtu.be/U0TXIXTzJEY?si=1Tupd7gzOQQhqCeL)<br>
   [Nhạc nền 2](https://youtu.be/QoHrfKZ5jno?si=0g4zs-rW3eS9G4hk)<br>
   [Nhạc nền 3](https://youtu.be/daFi4MScfl8?si=VuAmxG6SJmfQbaNc)<br>
   [Explosion](https://youtu.be/daFi4MScfl8?si=VuAmxG6SJmfQbaNc)<br>
   [Hit sound effect](https://youtu.be/iyuTagR1u44?si=FJULzoLCFXJpJ2iR)<br>
   [player shooting sound effect](https://youtu.be/FuvmTL1nPDs?si=8bs-oQyU3FLIU0sm)<br>
   [Enemies shooting sound effect](https://youtu.be/jz-awweTKw8?si=BOx02hFAmv3ELEsM)<br>
   [Main menu background music](https://www.youtube.com/watch?v=F6z1CH4oX2o&list=PL0QAEXDsccILdga79CcswY56cxSfLUXY9&index=13)<br>
   [Tiếng ăn vật phẩm](https://youtu.be/uTg0i6j7k34?si=nkSlcO_52h_jfpGp)<br>

2. Các nguồn hình ảnh:<br>
   [Background Menu Chính](https://za.pinterest.com/pin/54395107993157287/)<br>
   [Phông chữ 1](https://waxdroplet.itch.io/pixelart-alphabet)<br>
   [Phông chữ 2](https://arijkx.itch.io/free-pixel-art-blue-light-letters)<br>

   ___
   #**Checklist**
 Dùng các lệnh vẽ hình
 Texture
 Background
 Event bàn phím
 Event chuột
 Animation (hoạt hình)
 Xử lý va chạm
 Score (có tính điểm)
 Lưu bảng điểm
 Sound
 Sound on off
 Background music
 Font
 Menu
 Pause/Resume
 Status bar / lives (mạng/máu...)
   

       
