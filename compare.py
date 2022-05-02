import click
import matplotlib.pyplot as pyplot
import numpy as np
import os
import sys

python = os.path.join(os.path.dirname(__file__), 'python')

sys.path.insert(0, python)

@click.command('compare', help='Compare two .wav files', no_args_is_help=True, context_settings=dict(help_option_names=['-h', '--help']))
@click.argument('x')
@click.argument('y')
@click.option('-p', '--plot', is_flag=True, default=False, help='plot differences and exit')
@click.option('-r', '--rtol', default=0, show_default=True, help='set relative tolerance')
@click.option('-a', '--atol', default=0.1, show_default=True, help='set absolute tolerance')
def compare(x, y, plot, rtol, atol):

    from stftpitchshift.io import read

    x, srx = read(x)
    y, sry = read(y)

    assert srx == sry, f'Unequal sample rate {srx} != {sry}'
    assert x.shape == y.shape, f'Unequal array shape {x.shape} != {y.shape}'

    if plot:

        figure, (a, b) = pyplot.subplots(nrows=2, sharex=True)

        a.plot(x, label='x', color='blue', alpha=0.5)
        a.plot(y, label='y', color='red', alpha=0.5)
        b.plot(x - y, label='x - y', color='black', alpha=0.5)

        a.legend()
        b.legend()

        figure.tight_layout()

        pyplot.show()

    else:

        ok = np.allclose(x, y, rtol=rtol, atol=atol)

        print(':-)' if ok else ':-(')

if __name__ == '__main__':

    compare()
