import points_lines as pl
import math
import error_and_output as err

def exists_in_list(lst, element, mode=0):
	if element in lst:
		return True
	else:
		if mode == 0:
			lst.append(element)
			return False
		else:
			index=[]
			if element in lst:
				pass
			else:
				for i in range(len(lst)-1):
					p1=lst[i]
					p2=lst[i+1]
					d1=get_point(str(distance(p1,element) + distance(element,p2)))
					d2 = get_point(str(distance(p1, p2)))
					if d1 == d2:
						if (p1.x == element.x and p1.y == element.y) or (p2.x == element.x and p2.y == element.y):
							pass
						else:
							index.append(i+1)
					else:
						pass
				try:
					l1=lst[:index[0]]
					l2=lst[index[0]:]
					del lst[:]

					for j in l1:
						lst.append(j)
					lst.append(element)
					for j in l2:
						lst.append(j)
				except:
					pass
			return False


def onSegment(p1, p2, p3):
	if (p2.x <= max(p1.x, p3.x) and p2.x >= min(p1.x, p3.x) and p2.y <= max(p1.y, p3.y) and p2.y >= min(p1.y, p3.y)):
		return True
	return False


def find_final(p1, p2, q1, q2, o1, o2, o3, o4):
	if o1 != o2 and o3 != o4:
		return True
	# Special Cases
	# p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if o1 == 0 and onSegment(p1, p2, q1):
		return True
	# p1, q1 and q2 are colinear and q2 lies on segment p1q1
	if o2 == 0 and onSegment(p1, q2, q1):
		return True
		# p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if o3 == 0 and onSegment(p2, p1, q2):
		return True
	# p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if o4 == 0 and onSegment(p2, q1, q2):
		return True
	return False

def check_orientation(p1, p2, p3):
	val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y)
	if (val == 0):
		return 0  # colinear
	if val > 0:
		return 1
	else:
		return 2
		# return (val > 0)? 1: 2


def check_for_intersection(p1, q1, p2, q2):
	o1 = check_orientation(p1, q1, p2)
	o2 = check_orientation(p1, q1, q2)
	o3 = check_orientation(p2, q2, p1)
	o4 = check_orientation(p2, q2, q1)

	check = find_final(p1, p2, q1, q2, o1, o2, o3, o4)
	if check == False:
		return 'No'
	else:
		return 'Yes'


def find_intersection(p1, q1, p2, q2):
	"""Returns a point at which two lines intersect """
	try:
		x1, y1 = p1.x, p1.y
		x2, y2 = q1.x, q1.y
		x3, y3 = p2.x, p2.y
		x4, y4 = q2.x, q2.y
		xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
		xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
		xcoor =  xnum / xden

		ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
		yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
		ycoor = ynum / yden
		return pl.point(xcoor, ycoor),''
	except:
		try:
			d1=get_point(str(distance(p1,p2) + distance(p2,q1)))
			d2=get_point(str(distance(p1, q2) + distance(q2, q1)))
			df1=get_point(str(distance(p1,q1)))
			d3=get_point(str(distance(p2,p1) + distance(p1,q2)))
			d4=get_point(str(distance(p2, q1) + distance(q1, q2)))
			df2=get_point(str(distance(p2,q2)))
			if d1 == df1 and d2 == df1:
				return pl.point(p2.x,p2.y),pl.point(q2.x,q2.y)
			elif d3 == df2 and d4 == df2:
				return pl.point(p1.x, p1.y), pl.point(q1.x, q1.y)
			else:
				try:
					if d1 == df1 and d4 == df2:
						return pl.point(q1.x,q1.y),pl.point(p2.x,p2.y)
					else:
						return pl.point(q1.x,q1.y),pl.point(p2.x,p2.y)
				except:
					return '',''

		except:
			return '',''

def get_point(d1):
	try:
		point = d1.find('.')
		d1 = d1[:point + 5]
		return float(d1)
	except:
		return d1

def distance(p1,p2):
	return math.sqrt((p1.x - p2.x)**2 + (p1.y-p2.y) **2)

def search_intersections(global_dic,generic_list,intersections):
	try:
		for k, v in global_dic.items():
			found = False
			for k1, v1 in global_dic.items():
				if k1 != k and found == True:
					for i in range(len(v) - 1):
						for j in range(len(v1) - 1):
							a = check_for_intersection(v[i], v[i + 1], v1[j], v1[j + 1])
							if a == 'Yes':
								intersect1,intersect2 = find_intersection(v[i], v[i + 1], v1[j], v1[j + 1])
								try:
									exists_in_list(generic_list[k], v[i], 0)
								except:
									generic_list[k] = []
									generic_list[k].append(v[i])

								a = exists_in_list(generic_list[k], v[i + 1], 0)
								a = exists_in_list(generic_list[k], intersect1, 1)
								if intersect2 != '':
									a = exists_in_list(generic_list[k], intersect2, 1)

								try:
									a = exists_in_list(generic_list[k1], v1[j], 0)
								except:
									generic_list[k1] = []
									generic_list[k1].append(v1[j])

								a = exists_in_list(generic_list[k1], v1[j + 1], 0)
								a = exists_in_list(generic_list[k1], intersect1, 1)
								if intersect2 != '':
									a = exists_in_list(generic_list[k1], intersect2, 1)
								intersections.append(intersect1)
								if intersect2 != '':
									intersections.append(intersect2)
							else:
								pass
				else:
					if k1 == k:
						found = True
					else:
						pass
	except:
		pass