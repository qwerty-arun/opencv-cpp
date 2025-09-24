## 🔹 Gaussian Blur

- Uses a **Gaussian kernel** (a bell-shaped curve) to compute a weighted average of surrounding pixels.
- Nearby pixels influence the result more than far ones.
- Produces a **natural, smooth blur**.
- Good for:

  - Reducing noise
  - Preprocessing before edge detection (like Canny)
  - Making images look smoother

👉 Function: `cv::GaussianBlur()`

---

## 🔹 Median Blur

- Instead of averaging, it replaces each pixel with the **median value** of its neighborhood.
- Very effective for removing **salt-and-pepper noise** (random black & white pixels).
- Preserves edges better than Gaussian blur.
- Good for:

  - Noise reduction while keeping sharp edges
  - Cleaning up scanned documents or noisy photos

👉 Function: `cv::medianBlur()`

---

### ⚖️ Quick comparison

| Feature           | Gaussian Blur                      | Median Blur                         |
| ----------------- | ---------------------------------- | ----------------------------------- |
| Method            | Weighted average (Gaussian kernel) | Median of neighboring pixels        |
| Best for          | General smoothing, edge detection  | Removing salt-and-pepper noise      |
| Edge preservation | Blurs edges                        | Preserves edges better              |
| Speed             | Faster on large images             | Slower (needs sorting neighborhood) |

---

## 🔹 Gaussian Blur

```cpp
cv::GaussianBlur(
    InputArray src,       // Input image
    OutputArray dst,      // Output image
    Size ksize,           // Kernel size (width, height) -> must be odd and > 0
    double sigmaX,        // Gaussian kernel standard deviation in X direction
    double sigmaY = 0,    // (optional) in Y direction; if 0, same as sigmaX
    int borderType = cv::BORDER_DEFAULT // (optional) how image borders are handled
);
```

✅ Example:

```cpp
cv::GaussianBlur(image, blurred, cv::Size(5, 5), 1.5);
```

---

## 🔹 Median Blur

```cpp
cv::medianBlur(
    InputArray src,   // Input image
    OutputArray dst,  // Output image
    int ksize         // Aperture linear size; must be odd and > 1
);
```

✅ Example:

```cpp
cv::medianBlur(image, blurred, 5);
```

---

### ⚠️ Key points

- **Kernel size (`ksize`)** must always be **odd** (`3, 5, 7, …`).
- Gaussian blur has two extra parameters (`sigmaX`, `sigmaY`) that control how strong the blur is.
- Median blur only takes kernel size since it works on the median of the neighborhood.

---
