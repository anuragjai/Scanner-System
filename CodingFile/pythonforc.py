import os
source_dir = "C:/Users/Anurag/Desktop/Anurag/SourceFile"
file_name = input("Enter the file name:\n")
loc_cnt = 0
comment_cnt = 0
sloc_cnt = 0
lloc_cnt =0

#searched all file from the source_dir
for file in os.listdir(source_dir):
	#explored all file one by one and at the same time checking whether it is matched the entered file or not 
	if file.endswith(".c") and file_name==file:
		#joining the file name with its directory path so that we can get the full path of the given file
		new_path = os.path.join(source_dir, file)
		#print(new_path)
		with open(new_path) as fp:
		#reading the file line by line
			line_list = fp.read().splitlines()
			for line in line_list:
				if "/*" in line:
					comment_cnt = comment_cnt+1
					while("*/" not in line):
						comment_cnt = comment_cnt+1
						line_index = line_list.index(line)+1
						line = line_list[line_index]
				if not line.strip() or line.lstrip().startswith("//"):
					comment_cnt = comment_cnt+1

				# list 
				else:
					strip_str=line.lstrip()
					con_element= ["if","else","elseif","switch","for","goto","continue", "break"]
					for i in con_element:
						if strip_str.startswith(i):
							lloc_cnt= lloc_cnt+1

    		
			loc_cnt = len(line_list)
			sloc_cnt = loc_cnt-comment_cnt
			print("LOC= ", loc_cnt)
			print("Comments and space= ", comment_cnt)
			print("SLOC= ",sloc_cnt)
			print("LLOC= ",lloc_cnt)
			

			#LOC, comment, and SLOC find 