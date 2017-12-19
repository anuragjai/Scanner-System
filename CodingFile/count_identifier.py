import os
source_dir = "C:/Users/Anurag/Desktop/Anurag/SourceFile"
file_name = input("Enter the file name:\n")
#we are taking local variable only
for file in os.listdir(source_dir):
	if file.endswith(".c") and file_name==file:
		fun_count = 0
		ind_count = []
		new_path = os.path.join(source_dir, file)
		id_list= ['int','float','char','double','long double', 'void']
		with open(new_path) as fp:
			line_list = fp.read().splitlines()
			for line in line_list:   #check each line in file
				line = line.lstrip() #remove all left's blank space
				"""Code to ignore all multi line comments from the c file"""
				# if line.startswith("/*") and not line.endswith("*/"):
					# line_index = line_list.index(line)+1
					# while("*/" not in line):
						# line_index = line_list.index(line)+1
						# line = line_list[line_index]
						# print(line)			
				"""*****************main functionality *****************"""
				for i in id_list:				#iterate through all identifiers
					if line.startswith(i) and line.endswith(";"):				#check line starts with identifier
						splited_list = line.split(",")		#the no of element splited_list contain is the no of variable for that identifier
						if len(splited_list)==1:			#if length is one either functions or contain only one variable
							split_list = splited_list[0].split(" ")
							last_var = split_list[-1]
							if "=" in last_var:
								ind_count.append((last_var.split("="))[0])
							else:
								ind_count.append((last_var.split(";"))[0])
						else:							#contain more than one variables
							s = splited_list[0]
							del splited_list[0]
							split_s = s.split(" ")
							ind_count.append(split_s[-1])
							if "=" not in splited_list[-1]:
								last_elem = splited_list[-1].split(";")
								ind_count.append(last_elem[0])
								del splited_list[-1]
							for j in splited_list:		#iterate through the line which contain identifier
								if "=" in j:
									split_j = j.split("=")			#if string contain = sign spilt it and take 0th element which is variable
									ind_count.append(split_j[0])
								else:
									ind_count.append(j)
					if not line.startswith(i) and (i+" " in line) and not line.lstrip().startswith("//"):			#check identifier in for loop 
						ind_count.append(((line.split(";"))[0].split(" "))[-1])
					if line.startswith(i) and not line.endswith(";"):
						fun_count = fun_count+1
				total_iden = len(ind_count)
			print("Total identifier = ", total_iden,"\n")
			print("Number of function in program = ",fun_count,"\n")