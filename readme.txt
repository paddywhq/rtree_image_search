运行环境:
	windows7/windows8 32位/64位
	配置opencv环境(我们OpenCV版本为2.4.7)

文件夹内包含:
	README.avi: this file
	不同的特征文件:
		features_4.txt features_20.txt features_75.txt features_rgb9.txt output_5_2_2_std.txt
	R树代码:
		rtree.h:
			使用提供的alternative rtree
			增加了K近邻查找的功能
			增加了计算两个矩形最小距离的功能(矩形可以退化为点)
			增加了计算两个矩形最大距离的功能(矩形可以退化为点)
			增加了记录访问结点次数的功能
			所有增加代码在class RTree末尾(定义)和rtree.h末尾(实现)
	三个Main函数(使用前与rtree.h一起添加到工程，三个Main不可同时使用):
		RTreeKSearch_Main.cpp:
			对查询文件进行查询
			默认查询文件为color_feature.query，可以在RTreeKSearch_Main.cpp中更改文件读取
			默认特征向量文件为color_feature.txt，可以在RTreeKSearch_Main.cpp中更改文件读取
			默认维数为9，可以在RTreeKSearch_Main.cpp中更改宏定义
			默认数据量为5613(图片张数)，可以在RTreeKSearch_Main.cpp中更改宏定义
			默认查找数为11(查找结果包含查找输入图片)，可以在RTreeKSearch_Main.cpp中更改宏定义
			默认结果输出文件为result.txt，可以在RTreeKSearch_Main.cpp中更改文件读取
	IOCount_Main.cpp:
		测试R树访问结点次数
		默认特征向量文件为color_feature.txt，可以在RTreeKSearch_Main.cpp中更改文件读取
		默认维数为9，可以在RTreeKSearch_Main.cpp中更改宏定义
		默认数据量为5613(图片张数)，可以在RTreeKSearch_Main.cpp中更改宏定义
		默认查找数为10(查找结果包含查找输入图片)，可以在RTreeKSearch_Main.cpp中更改宏定义
		默认次数输出文件为IO_count.txt(输出每张图的访问结点次数)，可以在RTreeKSearch_Main.cpp中更改文件读取
		控制台窗口输出平均次数
	CorrectRate_Main.cpp:
		测试查询结果正确率
		默认特征向量文件为color_feature.txt，可以在RTreeKSearch_Main.cpp中更改文件读取
		默认维数为9，可以在RTreeKSearch_Main.cpp中更改宏定义
		默认数据量为5613(图片张数)，可以在RTreeKSearch_Main.cpp中更改宏定义
		默认查找数为11(查找结果包含查找输入图片)，可以在RTreeKSearch_Main.cpp中更改宏定义
		控制台窗口输出平均正确率(不包含原图片)		
	对于颜色特征提取，将会用到如下几个文件:
		ColorHistogram.h 其中包含了各种相关的条件编译开关，如转换HSV、将图像分块、使用高斯模糊等
						 并且，更为重要的是如需正确运行程序，需要在这里设置图像文件目录
		ColorHistogram.cpp 各种相关函数的实现文件
		ColorHistogramMain.cpp 批量进行图像颜色特征提取或仅对一张进行提取
	基于内容特征的提取尚不够完善，且注释不多，在此仅给出源代码，这些代码将会在下一次作业中进一步完善