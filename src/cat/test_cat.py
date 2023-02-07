import os
import unittest

def calc(flag=""):
    os.system(f"cat {flag} file.txt > a")
    os.system(f"./s21_cat {flag} file.txt > b")
    os.system(f"diff a b > res")

class TestCat(unittest.TestCase):

    def test_no_flag(self):
        calc()
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_b(self):
        calc("-b")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")
    
    def test_flag_e(self):
        calc("-e")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_n(self):
        calc("-n")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")
    
    def test_flag_s(self):
        calc("-s")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_t(self):
        calc("-t")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")


if __name__ == '__main__':
    unittest.main()

