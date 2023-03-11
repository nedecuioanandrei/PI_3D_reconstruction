import argparse 
import json
import sys


def convert(args) -> int:
    print("Converting {} ...".format(args.input))
    data = {}
    with open(args.input, "r") as f:
        f.readline()
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        f.readline()
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        f.readline()
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        a = f.readline().split()
        data[a[0]] = float(a[-1])
        a = f.readline().split()
        data[a[0]] = float(a[-1])

    with open(args.output, "w") as of:
        json.dump(data, of, indent=4)
    return 0


def main(argv) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input")
    parser.add_argument("output")
    parser.set_defaults(func=convert)

    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
