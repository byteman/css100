语言报警模块：

可以连续播放多个语音，语音播放的顺序采用先进先出方式。用作语音报警
目前只支持wav格式的文件

语音播放类：与业务无关
	audioplay.cpp
	audioplay.h
语音报警管理类：与业务相关
	audioalert.cpp

测试代码:
	test.cpp
	
依赖于开源的第三方库:
	PocoFoundation :基础类库
	portaudio: 音频播放
	sndfile:音频文件管理
