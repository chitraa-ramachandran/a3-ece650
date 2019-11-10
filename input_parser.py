import error_and_output as err
import re
class String_Parser:
    def parse_string(self,data):
        try:
            if data.startswith('a'):
                street_name, points = self.parse_sub(data)
                return 'a',street_name,points
            elif data.startswith('c'):
                street_name, points = self.parse_sub(data)
                return 'c',street_name,points
                #change_points(street_name, points)
            elif data.startswith('r'):
                pattern= re.compile(r'[r]\s+\"[a-zA-z0-9 ]*\"$')
                if pattern.match(data):
                    street_name = self.get_street_name(data[1:].strip())
                    return 'r',street_name,[]
                else:
                    err.print_error('Syntax Error for remove Street(r "street name")')
                    return 'r','',[]
            elif data.startswith('g'):
                if len(data) == 1:
                    return 'g','',[]
                else:
                    err.print_error('Wrong Command Entered')
                    return '','',[]
            else:
                err.print_error('you have to enter "a" or "c" or "r" or "g" at start of string')
                return '','',[]
        except:
            return '','',[]

    def parse_sub(self,parse_str):
        data = parse_str[1:]
        if len(data) > 0 and data[0].isspace():
            street_name = self.get_street_name(data)
            if street_name == '':
                return street_name.lower(), []
            else:
                points = self.extract_points(data)
                if points == []:
                    return street_name.lower(), []
                else:
                    return street_name.lower(), points
        else:
            if len(data) == 0:
                err.print_error('Street Name Required')
                return '', []
            if data[0]=='"':
                err.print_error('At least one space required between command and Street Name')
                return '',[]
            else:
                err.print_error('Some extra characters between command and Street Name')
                return '',[]

    def get_street_name(self,data):
        data=data.strip()
        if len(data) > 0 and data[0] == '"':
            start_index=data.find('"')
            end_index=data.rfind('"')
            if start_index == -1 or end_index == -1:
                err.print_error('Street name should be in "Street Name" format')
                return ''
            elif start_index == end_index:
                err.print_error('Street name should be in "Street Name" format')
                return ''
            else:
                for i in data[start_index+1:end_index]:
                    if i.isalnum() or i.isspace():
                        pass
                    else:
                        err.print_error('Street Name only contains Alpha and Spaces')
                        return ''
                street_name = data[start_index+1:end_index]
                return street_name.lower()
        else:
            if len(data) == 0:
                err.print_error('Street Name Required')
                return ''
            else:
                err.print_error('Some extra characters between command and Street name')
                return ''

    def extract_points(self,data):
        end_index = data.rfind('"')
        data=data[end_index+1:]
        if len(data) > 0 and data[0].isspace():
            data = data.strip()
            point_lst=[]
            if len(data) != 0:
                while True:
                    if len(data) > 0 and data[0] != '(':
                        err.print_error("Some Extra Characters are present in input")
                        return []
                    else:
                        index1=data.find('(')
                        index2=data.find(')')
                        if index1 != -1 and index2 == -1:
                            err.print_error("Enter Vertex in proper format (x,y) (Closing bracket Missing)")
                            return []
                        elif index1 == -1:
                            if len(point_lst) >= 2:
                                temp_list=[]
                                flag = ['False']
                                for p in point_lst:
                                    if tuple((p[0],p[1])) in temp_list:
                                        flag[0]='True'
                                        break
                                    else:
                                        temp_list.append(tuple((p[0],p[1])))
                                if flag[0] == 'False':
                                    return point_lst
                                else:
                                    err.print_error("Same vertex for more than one times (Same street cant be intersect)")
                                    return []
                            else:
                                err.print_error("Atleast Two Vertices Required")
                                return []
                        else:
                            try:
                                get_point=data[index1:index2+1]
                                pattern=re.compile(r'\(\s*\-*\d+\s*\,\s*\-*\d+\s*\)')
                                if pattern.match(get_point):
                                    get_point = get_point.replace(" ", "")
                                    point_lst.append(eval(get_point))
                                    data=data[index2 + 1:].strip()
                                else:
                                    err.print_error("Enter vertex in proper format (x,y)")
                                    return []
                            except:
                                err.print_error("Enter vertex in proper format (x,y) (int or float or double)")
                                return []
            else:
                err.print_error("Enter At least Two vertices")
                return []
        else:
            if len(data) == 0:
                err.print_error('Enter At least Two Vertices')
                return []
            elif len(data) > 0 and data[0]=='(':
                err.print_error('atleast one space required between Street Name and Vertices')
                return []
            else:
                err.print_error('Some extra characters between Street Name and Vertices')
                return []