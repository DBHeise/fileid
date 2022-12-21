from pkg_resources import require
import requests, json, argparse, os, subprocess, xmltodict

envDict = {}
ignoreFiles = [".gitignore",".gitattributes","LICENSE"]
ignoreExt = [".md",".txt",".json",".ps1",".py"]

def findBinaries(basefolder):
	testBinaries = []
	fileidBinaries = []
	for root, dirs, files in os.walk(basefolder):
		for file in files:
			if file.endswith("_test.exe") or file.endswith("_test"):
				testBinaries.append(os.path.join(root,file))
			elif file == "fileid.exe" or file == "fid" or file == "fileid":
				fileidBinaries.append(os.path.join(root,file))
	return fileidBinaries,testBinaries

def runTestBinary(file):
	print("Running Test: " + file)
	process = subprocess.Popen(file, shell=True, env=envDict)
	process.wait()
	return process.returncode == 0

def testfiles(fidbin, folder):
	allgood = True
	for root, dirs, files in os.walk(folder):
		if ".git" in dirs:
			dirs.remove('.git')
		for file in files:
			fullpath = os.path.join(root, file)
			file_name, file_ext = os.path.splitext(file)
			if not file_name in ignoreFiles and not file_ext in ignoreExt:
				allgood &= testfile(fidbin, fullpath)
	
	return allgood

def testfile(fid, file, format = "json"):
	outputStr = subprocess.check_output([fid, file, format])
	output = {}
	
	if format == "json":
		output = json.loads(outputStr)
	elif format == "xml":
		output = xmltodict.parse(outputStr)
	
	actual_ext = [extension["extension"].lower() for extension in output["extensions"]]
	
	filename, expected_ext = os.path.splitext(file)
	
	if "_" in expected_ext:
		expected_ext = expected_ext.replace(".","").replace("_",".").lower()
	else:
		expected_ext = expected_ext.replace(".","").lower()

	if expected_ext not in actual_ext:
		print("FAIL! (" + expected_ext + "!=" + ",".join(actual_ext) +") " + file)
		return False
	
	return True
		

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Run FILEID tests")    
	parser.add_argument("--build", required=True, help="path to build output")
	parser.add_argument("--files", required=True, help="path to directory containing test files")
	args = parser.parse_args()

	fileids, testbins = findBinaries(args.build)

	envDict = dict(os.environ)
	envDict["TESTFOLDER"] = args.files

	allgood = True

	## Run Unit Tests
	for testBin in testbins:
		allgood &= runTestBinary(testBin)		

	## Run Test Files
	for fid in fileids:
		allgood &= testfiles(fid, args.files)


	if not allgood:
		exit(-10)