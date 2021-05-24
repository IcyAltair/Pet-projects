from dataclasses import dataclass, field
from ctypes import windll
import os
from PIL import Image
import subprocess
from time import sleep
from typing import List
import win32gui
import win32ui
import win32con
import win32process


@dataclass
class Collector:
    mode: str = ""
    files: List = field(default_factory=list)
    file_names: List = field(default_factory=list)
    cur_dir: str = ""
    count: int = 0

    def path_finder(self):
        if self.mode == "auto":
            directory = os.getcwd()
            self.cur_dir = directory
            folders = os.walk(directory)
            for folder in folders:
                names = os.listdir(folder[0])
                for name in names:
                    fullname = os.path.join(folder[0], name)
                    if fullname.endswith(".py"):
                        self.files.append(fullname)
                for file_name in folder[2]:
                    if file_name.endswith(".py"):
                        self.file_names.append(file_name)

    def get_data(self):
        for i, file in enumerate(self.files):
            child_process = subprocess.Popen(
                # args=["cmd", "/c", "start", "/max","notepad.exe", file], stdout=subprocess.PIPE)# open notepad.exe in full size but hwnd is loss
                args=["notepad.exe", file], stdout=subprocess.PIPE)
            sleep(2.0)
            hwnd = self.get_hwnds_for_pid(child_process.pid)
            self.screenshot(hwnd[0], self.file_names[i])
            sleep(2.0)
            if child_process.poll() is None:
                child_process.terminate()

    def screenshot(self, hwnd=None, file_name=None):
        left, top, right, bot = win32gui.GetWindowRect(hwnd)
        w = right - left
        h = bot - top

        hwndDC = win32gui.GetWindowDC(hwnd)
        mfcDC = win32ui.CreateDCFromHandle(hwndDC)
        saveDC = mfcDC.CreateCompatibleDC()

        saveBitMap = win32ui.CreateBitmap()
        saveBitMap.CreateCompatibleBitmap(mfcDC, w, h)

        saveDC.SelectObject(saveBitMap)

        result = windll.user32.PrintWindow(hwnd, saveDC.GetSafeHdc(), 0)

        bmpinfo = saveBitMap.GetInfo()
        bmpstr = saveBitMap.GetBitmapBits(True)

        im = Image.frombuffer(
            'RGB',
            (bmpinfo['bmWidth'], bmpinfo['bmHeight']),
            bmpstr, 'raw', 'BGRX', 0, 1)

        win32gui.DeleteObject(saveBitMap.GetHandle())
        saveDC.DeleteDC()
        mfcDC.DeleteDC()
        win32gui.ReleaseDC(hwnd, hwndDC)

        if result == 1:
            if os.path.exists(os.path.join(self.cur_dir, file_name)+".screenshot.png")\
            or os.path.exists(os.path.join(self.cur_dir, file_name)+".screenshot"+str(self.count)+".png"):
                self.count += 1
                im.save(os.path.join(self.cur_dir, file_name) +
                        ".screenshot"+str(self.count)+".png")
            else:
                im.save(os.path.join(self.cur_dir, file_name)+".screenshot.png")

    def get_hwnds_for_pid(self, pid):
        def callback(hwnd, hwnds):
            found_pid = 0
            if win32gui.IsWindowVisible(hwnd) and win32gui.IsWindowEnabled(hwnd):
                _, found_pid = win32process.GetWindowThreadProcessId(hwnd)
            if found_pid == pid:
                hwnds.append(hwnd)
            return True
        hwnds = []
        win32gui.EnumWindows(callback, hwnds)
        return hwnds

    def print_res(self):
        for file in self.files:
            print(file)
        for file_name in self.file_names:
            print(file_name)


def main():
    c = Collector("auto")
    c.path_finder()
    # c.print_res()
    c.get_data()


if __name__ == '__main__':
    main()
