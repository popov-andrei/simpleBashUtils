import os
import unittest


def calc(pattern, flag):
    os.system(f"grep {pattern} {flag} 1.file 2.file 3.file > a")
    os.system(f"./s21_grep {pattern} {flag} 1.file 2.file 3.file > b")
    os.system(f"diff a b > res")


def calc_2(flag):
    os.system(f"grep {flag} 4.file 1.file > a")
    os.system(f"./s21_grep {flag} 4.file 1.file > b")
    os.system(f"diff a b > res")


class TestCat(unittest.TestCase):

    def test_no_flag(self):
        calc("reflect", "")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_i(self):
        calc("trulyalya", "-i")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_v(self):
        calc("s", "-v")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_c(self):
        calc("s", "-c")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_l(self):
        calc("s", "-l")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_n(self):
        calc("s", "-n")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_o(self):
        calc("123", "-o")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_h(self):
        calc("reflect", "-h")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_s(self):
        calc("123123", "-s")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_f(self):
        calc_2("-f")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_in(self):
        calc("trulyalya", "-in")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_cv(self):
        calc("s", "-cv")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_iv(self):
        calc("s", "-iv")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_lv(self):
        calc("s", "-lv")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_ho(self):
        calc("reflect", "-ho")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")

    def test_flag_nf(self):
        calc_2("-nf")
        self.assertEqual(os.path.getsize("res"), 0, "Diff size should be 0")


if __name__ == '__main__':
    unittest.main()
