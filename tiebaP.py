# -*- coding:utf-8 -*-

#urllib模块提供了读取Web页面数据的接口
import urllib
import urllib2
#re模块主要包含了正则表达式
import re
#os模块提供了非常丰富的方法用来处理文件和目录
import os
#定义一个getHtml()函数
def getHtml(url):
   	page = urllib.urlopen(url)
   	html = page.read().decode('utf8') #read()方法用于读取URL上的数据
	return html

def getImg(html):
	patternImg = re.compile('<img class="BDE_Image" src="(.*?)"',re.S)
	images = re.findall(patternImg,html)
	return images

def saveImgs(images,name):
	number=1
	print u"共有",len(images),u"张照片"
	for imageURL in images:
		splitPath=imageURL.split('.')
		fTail=splitPath.pop()#fTail是指文件后缀 .pop是移除列表List中的一个元素（默认最后一个）
		if len(fTail)>3:
			fTail="jpg"
		filename=name+"/"+str(number)+"."+fTail
		saveImg(imageURL,filename)
		number+=1

def saveImg(imageURL,filename):
	u=urllib.urlopen(imageURL)
	data=u.read()
	f=open(filename,'wb')
	f.write(data)
	f.close()

def mkdir(path):
	path=path.strip()#移除字符串头尾指定的字符
	isExists=os.path.exists(path)
	#判断结果
	if not isExists:
		os.makedirs(path)
		print u"名为",path,'的文件夹已经创建成功'
		return True
	else:
		print u"名为",path,'的文件夹已经存在'
		return False

pageIndex=input("Input index of web page: ")#注意raw_input()和input()的区别
siteURL='http://tieba.baidu.com/p/4453774367'
url=siteURL+'?pn='+str(pageIndex)		
html = getHtml(url)
images=getImg(html)
path='mm_p'+str(pageIndex)
mkdir(path)
saveImgs(images,path)
