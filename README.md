# infix2postfix-complex-calculations

Calculate Infix2Postfix Notations and Results Step-by-Step

```cpp
2*(sin(pi/4)+e^(ln(2)+1))/2*pi
```

---

## Compiling and Running Application

---

**On Windows**

Use cmake-clean-configure-build-install.bat on a command-line

write cmd to address bar to enter command-line interface

```batch
cmake-clean-configure-build-install.bat
```

| Description            | Folder      |
| ---------------------- | ----------- |
| Solution Directory     | build_win   |
| Release Directory      | release_win |
| Installation Directory | publish_win |

---

**On WSL (Ubuntu Linux)**

Use cmake-clean-configure-build-install.sh on a command-line 

write wsl to address bar to enter command line interface, if you are working on windows you need to update your file encoding and permission

| Description            | Folder        |
| ---------------------- | ------------- |
| Solution Directory     | build_linux   |
| Release Directory      | release_linux |
| Installation Directory | publish_linux |

Give executable permission to script

```bash
chmod +x cmake-clean-configure-build-install.sh
```

 Convert encoding

```bash
dos2unix cmake-clean-configure-build-install.sh
```

and Run Script

```bash
./cmake-clean-configure-build-install.sh
```

---

## Result Validation and ScreenShots

---

### Google Calculator

[hesapla 2*(sin(pi/4)+e^(ln(2)+1))/2*pi - Google'da Ara](https://www.google.com/search?q=hesapla+2*%28sin%28pi%2F4%29%2Be%5E%28ln%282%29%2B1%29%29%2F2*pi&sca_esv=f6a0e070fa17b360&sxsrf=ADLYWILLtwIKWNKPY9-a4K9DRvF9z2xLTQ%3A1728311735751&ei=t_EDZ9W5Lb6Wxc8PgJbq6QI&ved=0ahUKEwiV8cf4vvyIAxU-S_EDHQCLOi0Q4dUDCA8&uact=5&oq=hesapla+2*%28sin%28pi%2F4%29%2Be%5E%28ln%282%29%2B1%29%29%2F2*pi&gs_lp=Egxnd3Mtd2l6LXNlcnAiJmhlc2FwbGEgMiooc2luKHBpLzQpK2VeKGxuKDIpKzEpKS8yKnBpSLwGUABY4QVwAHgBkAEAmAGkAqABtwiqAQUwLjUuMbgBA8gBAPgBAZgCAKACAJgDAJIHAKAHuAQ&sclient=gws-wiz-serp)

![](assets/2024-10-07-19-03-29-image.png)

---

## Windows

![](assets/2024-10-07-22-57-06-image.png)

---

### Linux WSL

![](assets/2024-10-07-22-57-33-image.png)

---

## Wokwi ESP32-S3 / Arduino

**Project Link**

[infix2postfix - Wokwi ESP32, STM32, Arduino Simulator](https://wokwi.com/projects/411097412978595841)

**ScreenShots**

![](assets/2024-10-07-19-04-54-image.png)

---
