#changes line 6,189, 188, 178, 159, 145, 151, 152
import sys
import collections
def print_error(error_msg):
	#print('Error: '+error_msg)
	print 'Error: '+error_msg

global_output = collections.OrderedDict()
global_edges = []

def check_for_element_in_dic(d,v):
	for k1,v1 in d.items():
		if v.x == v1.x and v.y == v1.y:
			return True
	return False

def search_key(d,v):
	for k1,v1 in d.items():
		if v1 != '':
			if v.x == v1.x and v.y == v1.y:
				return k1
	return -1

def display_output(global_dic_for_result,global_intersections):
	try:
		all_points=[]
		for k,v in global_dic_for_result.items():
			for i in v:
				if (i.x,i.y) in all_points:
					pass
				else:
					all_points.append(tuple((i.x,i.y)))
		count = 0
		for point in all_points:
			global_output[str(count)] = point
			count = count + 1

		unique_intersections=[]
		for i in global_intersections:
			point=tuple((i.x,i.y))
			if point not in unique_intersections:
				unique_intersections.append(point)
		print_output(global_dic_for_result,unique_intersections)
	except:
		pass

def print_output(global_dic_for_result,unique_intersections):
	#print("V",len(global_output))
	sys.stdout.write('V '+str(len(global_output))+'\n')
	#print("V = {")
	#for k, v in global_output.items():
	#	x= round(v[0],2)
	#	y= round(v[1],2)
	#	if x == -0.00:
	#		x=0.00
	#	if y == -0.00:
	#		y=0.00
	#	print k, ':',tuple((x,y))
		#print(k+':'+str(tuple((x,y))))
	#print "}"
	#print("}")
	global_edges[::] = []
	unique_edges=[]
	#print('E {',end='')
	sys.stdout.write('E {')
	#print "E {",
	
	for k, v in global_dic_for_result.items():
		for i in range(len(v)-1):
			if (tuple((v[i].x,v[i].y)) in unique_intersections):					
				e1=search_index_in_dic(global_output,tuple((v[i].x,v[i].y)))
				e2=search_index_in_dic(global_output,tuple((v[i+1].x,v[i+1].y)))
				if (e1,e2) in unique_edges:
					pass
				else:
					unique_edges.append(tuple((e1,e2)))
			elif tuple((v[i+1].x,v[i+1].y)) in unique_intersections:
				e1=search_index_in_dic(global_output,tuple((v[i].x,v[i].y)))
				e2=search_index_in_dic(global_output,tuple((v[i+1].x,v[i+1].y)))
				if (e1,e2) in unique_edges:
					pass
				else:
					unique_edges.append(tuple((e1,e2)))
	temp_edges=[]
	for edge in unique_edges:
		if tuple((edge[0],edge[1])) in temp_edges:
			pass
		elif tuple((edge[1],edge[0])) in temp_edges:
			pass
		else:
			temp_edges.append(tuple((edge[0],edge[1])))
	
	#for edge in temp_edges:
		#print('<'+edge[0]+','+edge[1]+'>')
	#	print '<' + edge[0] + ',' + edge[1] + '>'
	for e in range(len(temp_edges)):
		if e == len(temp_edges)-1:
			#print('<' + temp_edges[e][0] + ',' + temp_edges[e][1] + '>',end='')
			sys.stdout.write('<' + str(temp_edges[e][0]) + ',' + str(temp_edges[e][1]) + '>')
		else:
			#print('<' + temp_edges[e][0] + ',' + temp_edges[e][1] + '>,',end='')
			sys.stdout.write('<' + str(temp_edges[e][0]) + ',' + str(temp_edges[e][1]) + '>,')
	#print("}")
	sys.stdout.write('}\n')
	#print("s 1 5")
	#print "}"
	global_output.clear()

def search_index_in_dic(d,v):
	for k1,v1 in d.items():
		if v1 == v:
			return k1

def get_last_index_dic(d):
	if len(d) == 0:
		return 0
	else:
		count=1
		for k,v in d.items():
			if count == len(d):
				return k
			count = count + 1