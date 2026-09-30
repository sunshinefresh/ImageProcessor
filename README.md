# ImageProcessor 과제 제출

## 구현 항목

- Grayscale 변환
- 밝기 / 대비 조절
- 이진화(Thresholding)
- 3x3 Convolution 필터 (Blur / Sharpen)
- 히스토그램 분석
- 이미지 Crop / Resize
- 상하 / 좌우 반전
- FilterBase 추상 클래스 기반 필터 구조
- 필터 파이프라인 체인
- std::thread 기반 멀티스레드 처리
- 처리 시간 및 실행 결과 로그 파일 출력

## 실행 명령어 (예시)

```powershell
# Grayscale 변환
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_grayscale.bmp --filter grayscale
```

```powershell
# 밝기 조절
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_brightness.bmp --filter brightness:50
```

```powershell
# 대비 조절
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_contrast.bmp --filter contrast:1.5
```

```powershell
# Thresholding
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_threshold.bmp --filter threshold:128
```

```powershell
# 3x3 Convolution - Blur
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_blur.bmp --filter blur
```

```powershell
# 3x3 Convolution - Sharpen
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_sharpen.bmp --filter sharpen
```

```powershell
# 히스토그램 분석
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_histogram.bmp --filter histogram
```

```powershell
# 이미지 Crop (x, y, width, height)
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_crop.bmp --filter crop:100,100,300,300
```

```powershell
# 이미지 Resize (width, height)
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_resize.bmp --filter resize:320,240
```

```powershell
# 좌우 반전
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_flip_horizontal.bmp --filter flip:horizontal
```

```powershell
# 상하 반전
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_flip_vertical.bmp --filter flip:vertical
```

```powershell
# 필터 파이프라인 체인
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_pipeline.bmp --pipeline "grayscale,blur,threshold:128"
```

```powershell
# 멀티스레드 처리
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_thread.bmp --filter grayscale --threads 4
```

```powershell
# 로그 파일 출력
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_log.bmp --filter grayscale --threads 4 --log processing.log
```

```powershell
# 파이프라인 + 멀티스레드 + 로그
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_pipeline.bmp --pipeline "grayscale,blur,threshold:128" --threads 4 --log processing.log
```