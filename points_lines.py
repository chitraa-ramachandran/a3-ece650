import ece650-a1 as main_file
import error_and_output as err
def pp(x):
    if isinstance(x, float):
        if x.is_integer():
            return str(int(x))
        else:
            return "{0:.2f}".format(x)
    return str(x)

class point(object):
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def __repr__(self):
        return '(' + pp(self.x) + ', ' + pp(self.y) + ')'


class line(object):
    def __init__(self, src, dst):
        self.src = src
        self.dst = dst

    def __repr__(self):
        return '['+ str(self.src) + '-->' + str(self.dst) + ']'

def add_points(street_name,points):
    flag=main_file.check_for_street(street_name)
    if flag == False:
        final_points=[]
        for p in points:
            final_points.append(point(p[0],p[1]))
        return final_points
    else:
        err.print_error('Street already exists\n')

def change_points(street_name,points):
    final_points = []
    for p in points:
        final_points.append(point(p[0], p[1]))
    return final_points
