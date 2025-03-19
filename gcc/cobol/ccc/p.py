def main():
  print("Hello")
  f = open("xxx.c", 'w')
  for i in range(10):
    f.write("    LEFT\n")
    f.write("    STATIC int a{} = {};\n".format(i, i))
    f.write("               a{} = a{} + n;\n".format(i, i))
    f.write("    foo(a{});\n".format(i))
    f.write("    RIGHT\n")
  f.close()
main()
