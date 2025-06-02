from pynput import mouse, keyboard
import time
import threading
print("Space=Start\nBackspace=Stop")
clicking = False

def clicker():
    global clicking
    while True:
        if clicking:
            mouse.Controller().click(mouse.Button.left, 1)

def on_press(key):
    global clicking
    if key == keyboard.Key.space:
        clicking = True


def on_release(key):
    global clicking
    if key == keyboard.Key.backspace:
        clicking = False
        return False

click_thread = threading.Thread(target=clicker)
click_thread.daemon = True
click_thread.start()

with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()

print("Script finished.")
