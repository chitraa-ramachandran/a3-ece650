import sys
import input_parser
import points_lines as pl
import intersection_logic as il
import error_and_output as err
import collections
# YOUR CODE GOES HERE

global_dic=collections.OrderedDict()
global_dic_for_result=collections.OrderedDict()
global_intersections=[]


def main():
    ### YOUR MAIN CODE GOES HERE
    while True:
        
        try:
            data = sys.stdin.readline().strip()
            try:
                if data == '':
                    break
                p1 = input_parser.String_Parser()
                type,street_name,points=p1.parse_string(data)
                if type == 'a':
                    if street_name == '' or points == []:
                        pass
                    else:
                        final_points=pl.add_points(street_name, points)
                        if check_for_street(street_name):
                            err.print_error("'a' specified for a street that already exist.")
                        else:
                            global_dic[street_name] = final_points
                elif type == 'c':
                    if street_name == '' or points == []:
                        pass
                    else:
                        points=pl.change_points(street_name,points)
                        if check_for_street(street_name):
                            if len(points) > 0:
                                global_dic[street_name]=points
                        else:
                            err.print_error("'c' specified for a street that does not exist.")
                elif type == 'r':
                    if street_name != '':
                        if check_for_street(street_name):
                            del global_dic[street_name]
                        else:
                            err.print_error("'r' specified for a street that does not exist.")
                elif type == 'g':
                    global_dic_for_result.clear()
                    global_intersections[::]=[]
                    il.search_intersections(global_dic,global_dic_for_result,global_intersections)
                    err.display_output(global_dic_for_result,global_intersections)
                    sys.stdout.flush()
                    #break
            except:
                err.print_error("Try Again")
        except:
            break

def check_for_street(street_name):
    if street_name in global_dic.keys()	:
        return True
    else:
        return False

if __name__ == '__main__':
    main()
