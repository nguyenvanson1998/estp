from time import process_time
import numpy as np

from utilities.point import Point
from utilities.prim import MST

from paper.local_search import local_search


def percent_reduction(l_T, l_MST):
    return 100.0 * (l_MST - l_T) / l_MST


def read_input(f_inp):
    length = int(f_inp.readline())
    X = []
    for _ in range(length):
        X.append(Point.from_line(f_inp.readline()))

    return X


def read_optimal(f_opt):
    opt = float(f_opt.readline())
    mst = float(f_opt.readline())

    steiner_cnt = f_opt.readline()
    for _ in range(int(steiner_cnt)):
        f_opt.readline()

    return opt, mst


def run_instance(f_inp, run_times):
    X = read_input(f_inp)
    mst = MST(X).l

    best_phi = 0.0
    avg_phi = 0.0
    avg_time = 0.0

    for _ in range(run_times):
        elapsed_time = process_time()
        T, S = local_search(X)
        elapsed_time = process_time() - elapsed_time

        phi = percent_reduction(round(T.l, 9), mst)
        best_phi = max(best_phi, phi)
        avg_phi += phi
        avg_time += elapsed_time

    avg_phi /= run_times
    avg_time /= run_times

    return best_phi, avg_phi, avg_time


def get_phi(X, mst, p):
    T, S = local_search(X, _l=p, _u=p)
    return percent_reduction(round(T.l, 9), mst)


def run_instance_parallel(X, mst, run_times, p, pool):
    results = pool.starmap_async(get_phi, [(X, mst, p) for _ in range(run_times)]).get()
    return sum(results) / run_times


def process_file(path: str, label: str, f_out, run_count):
    results = np.zeros(3, dtype=float)

    with open(path) as f_inp:
        print(path)
        test_cases = int(f_inp.readline())

        for i in range(test_cases):
            test_res = run_instance(f_inp, run_count)
            results += np.array(test_res)

        results /= test_cases

        f_out.write(label + ' ' + ' '.join([str(round(res, 2)) for res in results]) + '\n')
