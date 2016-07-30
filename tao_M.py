# -*- coding:utf-8 -*-

import urllib
import urllib2
import re
import tool
import os

class Spider:
 
    def __init__(self):
        self.siteURL = 'http://mm.taobao.com/json/request_top_list.htm'
 
    def getPage(self,pageIndex):
        url = self.siteURL + "?page=" + str(pageIndex)
        print url
        request = urllib2.Request(url)
        response = urllib2.urlopen(request)
        return response.read().decode('gbk')
 
    def getContents(self,pageIndex):
        page = self.getPage(pageIndex)
        pattern = re.compile('<div class="list-item".*?pic-word.*?<a href="(.*?)".*?<img src="(.*?)".*?<a class="lady-name.*?>(.*?)</a>.*?<strong>(.*?)</strong>.*?<span>(.*?)</span>',re.S)
        items = re.findall(pattern,page)
        contents = []
        for item in items:
            contents.append([item[0],item[1],item[2],item[3],item[4]])
	return contents

    #获取MM个人详情页面
    def getDetailPage(self,infoURL):
        response = urllib2.urlopen(infoURL)
	#print response.read().decode('gbk')
        return response.read().decode('gbk')

    #获取页面所有图片
    def getAllImg(self,page):
        #pattern = re.compile('<>(.*?)<>',re.S)
        #个人信息页面所有代码
        #content = re.search(pattern,page)
	#print page
        #从代码中提取图片
	reg = r'src="(.+?\.jpg)" pic_ext'
        patternImg = re.compile(reg)
        images = re.findall(patternImg,page)
        return images

    #保存多张写真图片
    def saveImgs(self,images,name):
        number = 1
        print u"发现",name,u"共有",len(images),u"张照片"
        for imageURL in images:
            splitPath = imageURL.split('.')
            fTail = splitPath.pop()#fTail是指文件后缀
            if len(fTail) > 3:
                fTail = "jpg"
            fileName = name + "/" + str(number) + "." + fTail
            self.saveImg(imageURL,fileName)
            number += 1

	#传入图片地址，文件名，保存单张图片
    def saveImg(self,imageURL,fileName):
         u = urllib.urlopen(imageURL)
         data = u.read()
         f = open(fileName, 'wb')
         f.write(data)
         print u"正在悄悄保存她的一张图片为",fileName
         f.close()
 
    #创建新目录
    def mkdir(self,path):
        path = path.strip()
        # 判断路径是否存在
        # 存在     True
        # 不存在   False
        isExists=os.path.exists(path)
        # 判断结果
        if not isExists:
            # 如果不存在则创建目录
            print u"偷偷新建了名字叫做",path,u'的文件夹'
            # 创建目录操作函数
            os.makedirs(path)
            return True
        else:
            # 如果目录存在则不创建，并提示目录已存在
            print u"名为",path,'的文件夹已经创建成功'
            return False

	#将一页淘宝MM的信息保存起来
    def savePageInfo(self,pageIndex):
        #获取第一页淘宝MM列表
        contents = self.getContents(pageIndex)
        for item in contents:
            #item[0]个人详情URL,item[1]头像URL,item[2]姓名,item[3]年龄,item[4]居住地
            print u"发现一位模特,名字叫",item[2],u"芳龄",item[3],u",她在",item[4]
            print u"正在偷偷地保存",item[2],"的信息"
            print u"又意外地发现她的个人地址是",item[0]
            #个人详情页面的URL
            detailURL = 'http:'+item[0]
            #得到个人详情页面代码,并将页面编码转成gbk格式
            detailPage = self.getDetailPage(detailURL)
            #获取所有图片列表
            images = self.getAllImg(detailPage)
            self.mkdir(item[2])
            #保存图片
            self.saveImgs(images,item[2])
 
spider = Spider()
spider.savePageInfo(2)
