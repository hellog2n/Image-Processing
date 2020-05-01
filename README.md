# 영상 처리 과제

 

# 1. gray-scale 비트맵 영상의 negative 영상 만들기
파일명 : bitmapTest
   -교과서 39페이지(리스트 3-2)

   -입력 영상: "talent.bmp"

-------

# 2. color 비트맵 영상의 negative 영상 만들기
파일명 : colorBitmapNegative
   -교과서 49페이지(리스트 3-4)
   -입력 영상: "pshop256.bmp"

----
# 3. raw 이미지 생성하기

* 코드에 메인 함수가 중복되게 작성했습니다.


(1) gray-scale 영상 생성
- 출력 파일 이름 : sample_image.raw
- 영상의 크기 : 256*256
- 명도 값
   상단 좌측 블록 : 0
   상단 우측 블록 : 64
   하단 좌측 블록 : 192
   하단 우측 블록 : 255

(2) color 영상 4분할로 생성
- 출력 파일 이름 : sample_color_image.raw
- 영상의 크기 : 256*256
- 명도 값
   상단 좌측 블록 : red
   상단 우측 블록 : green
   하단 좌측 블록 : blue
   하단 우측 블록 : black




(3) 모자이크 영상 생성
- 입력파일 이름 : Lenna.raw
- 출력파일 이름 : masaic_image.raw
- 영상의 크기 : 256*256
- Block의 크기 : 8*8
- 32 blocks / row
- 32 blocks / column
-----

# 4. BMP 비트맵 이미지 생성하기

(1) color 영상 4분할로 생성
- 출력 파일 이름 : sample_color_image.bmp
- 영상의 크기 : 256*256
- 명도 값
   상단 좌측 블록 : red
   상단 우측 블록 : green
   하단 좌측 블록 : blue
   하단 우측 블록 : black


(2) color 영상 4분할 일직선으로 생성
- 출력 파일 이름 : sample_color_image2.bmp
- 영상의 크기 : 256*256


(3) gray scale 영상 4분할로 생성
- 출력 파일 이름 : sample_image.bmp
- 영상의 크기 : 256*256
- 명도 값
   상단 좌측 블록 : 0
   상단 우측 블록 : 64
   하단 좌측 블록 : 192
   하단 우측 블록 : 255





----------
책 참고 : Visual C++와 OpenCV로 배우는 디지털 영상처리
