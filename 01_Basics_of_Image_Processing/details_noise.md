### **Header Inclusions**

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
```

* `opencv2/opencv.hpp` → Includes all the core OpenCV functionality (image processing, GUI, etc.).
* `iostream` → For input/output with `cout` and `cin`.

---

### **Namespaces**

```cpp
using namespace std;
using namespace cv;
```

* `std` → Avoids writing `std::cout`, etc.
* `cv` → Avoids writing `cv::Mat`, etc.

---

### **Constants**

```cpp
const int max_value_H = 360 / 2;
const int max_value = 255;
```

* In OpenCV, **Hue values** in HSV color space range from `0–179` instead of `0–360`.
  → That’s why `360/2 = 180`.
* `max_value = 255` → Maximum range for **Saturation** and **Value** components.

---

### **Main Function**

```cpp
int main(){
```

Entry point of the program.

---

### **Image Paths**

```cpp
    string image_path1 = "D:/opencv-cpp/images/black_hole.jpg";
    string image_path2 = "D:/opencv-cpp/images/light.png";
    string image_path3 = "D:/opencv-cpp/images/tesla.png";
```

* You store different file paths for images.
* Only `image_path2` (light.png) is actually used.

---

### **Read and Resize Image**

```cpp
    Mat image1 = imread(image_path2, IMREAD_COLOR);
    resize(image1, image1, {500, 500});
```

* `imread()` loads the image as a 3-channel **BGR color image**.
* `resize()` scales it to **500×500 pixels**.

---

### **Check if Image is Loaded**

```cpp
    if(image1.empty()){
        cout << "Could not read the image" << endl;
        return -1;
    }
```

* If `imread()` fails (file not found, wrong path, etc.), `image1` will be empty.
* The program prints an error and exits.

---

### **Lower Bound Values**

```cpp
    vector<int> lower_bound = {170, 80, 50};
```

* These are your manually chosen **HSV lower-bound values**:

  * `170` → Hue (close to red/purple colors).
  * `80` → Saturation (medium color intensity).
  * `50` → Value (brightness).

---

### **Set HSV Range**

```cpp
    int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
    int high_H = max_value_H, high_S = max_value, high_V = max_value;
```

* Lower threshold = `{170, 80, 50}`.
* Upper threshold = `{180, 255, 255}`.
* So your code is detecting **all pixels with Hue in 170–180, Sat in 80–255, and Value in 50–255**.

---

### **Convert to HSV and Threshold**

```cpp
    Mat hsvImg, imgThreshold;

    cvtColor(image1, hsvImg, COLOR_BGR2HSV);
    inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);
```

1. `cvtColor()` → Converts the image from BGR (default in OpenCV) to HSV.
2. `inRange()` → Creates a **binary mask** (`imgThreshold`) where:

   * White (255) = pixel is within HSV range.
   * Black (0) = pixel is outside range.

---

### **Apply Blurring**

```cpp
    Mat medianBlurImg, gaussianBlurImg;
    medianBlur(image1, medianBlurImg, 9);
    GaussianBlur(image1, gaussianBlurImg, Size(1, 1), 9, 9);
```

* `medianBlur(image1, medianBlurImg, 9)` → Applies a **median filter** (kernel size = 9). Good for removing salt-and-pepper noise.
* `GaussianBlur(image1, gaussianBlurImg, Size(1, 1), 9, 9)` → Applies a **Gaussian filter**.

  * `Size(1, 1)` looks strange (normally >1), but because you specify sigmaX = 9, sigmaY = 9, the kernel size is actually computed automatically.

*(Note: you commented out the imshow for blurred images.)*

---

### **Display Images**

```cpp
    imshow("Original Image", image1);
    imshow("HSV Image", hsvImg);
    imshow("Threshold Image", imgThreshold);
```

* Opens 3 windows:

  * Original BGR image.
  * Converted HSV image.
  * Thresholded binary mask.

---

### **Wait for Key and Exit**

```cpp
    int k = waitKey(0);

    if(k == 'q'){
        cv::destroyAllWindows();
    }
    return 0;
}
```

* `waitKey(0)` → Waits indefinitely for a key press.
* If user presses `'q'`, all windows are closed.
* Program exits with `0` (success).

---

✅ **In summary:**

* You load and resize an image.
* Convert it to HSV.
* Extract colors in a specific HSV range.
* Apply blurring for noise reduction (though not used later).
* Show original, HSV, and thresholded versions.

---

Do you want me to also explain **why you used HSV instead of BGR** for thresholding?

You used **HSV instead of BGR** because HSV is much better suited for **color detection and segmentation**. Let’s break it down:

---

### **BGR Color Space (default in OpenCV)**

* Images in OpenCV are loaded as **BGR (Blue, Green, Red)**.
* Each pixel has 3 values (B, G, R).
* The problem:

  * Colors are a **mix of three values**, so separating a single color is tricky.
  * Example: The color **red** in BGR could look like `(0,0,255)`, `(10,10,200)`, `(50,50,180)`, etc., depending on lighting.
  * It’s **sensitive to brightness and shadows**.

---

### **HSV Color Space (Hue, Saturation, Value)**

* **Hue (H)** → Represents the actual *color* (0–179 in OpenCV).

  * Red ≈ 0 or 180, Green ≈ 60, Blue ≈ 120, etc.
* **Saturation (S)** → Intensity of the color (0–255).

  * 0 = gray, 255 = pure color.
* **Value (V)** → Brightness (0–255).

  * 0 = black, 255 = maximum brightness.

---

### **Why HSV is better for color detection**

✅ In HSV, the **color information (Hue)** is separate from **brightness (Value)**.
✅ You can easily define a range for a color just using Hue (with some tolerance).
✅ Saturation & Value help filter out unwanted dull or very bright regions.

---

### **Example: Detecting Red**

In BGR:

* Red could be `(0,0,255)`, `(10,20,200)`, `(100,50,50)` depending on lighting.
* Hard to set a threshold because all three values vary a lot.

In HSV:

* Red has `Hue ≈ 0 (or 180)`.
* You just need: `H in [170, 180]` or `H in [0, 10]`.
* Much simpler, more robust to brightness and shadows.

---

👉 That’s why your code used this part:

```cpp
cvtColor(image1, hsvImg, COLOR_BGR2HSV);
inRange(hsvImg, Scalar(170, 80, 50), Scalar(180, 255, 255), imgThreshold);
```

* It specifically finds all **red-ish pixels** in the image.
* Works even if brightness changes, because Hue stays fairly stable.

---