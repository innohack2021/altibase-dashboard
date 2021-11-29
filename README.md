# **ALTIBASE - Standard BMT Visualization & Realtime Monitoring System**
## **개발 목적**
1. 알티베이스 버전 업데이트시 성능 확인 및 검증을 위한 Standard BMT를 진행하고, 그 결과를 분석하기 위하여 그래프로 데이터 시각화를 진행.
2. 알티베이스 데이터를 Python 기반 웹 프레임워크인 Django와 연결하여 알티베이스의 확장성을 높힘.
3. 오픈 소스를 활용하여 알티베이스 DB와 서버의 실시간 상태 모니터링을 위한 Dashboard 제작.
## **소프트웨어 환경 및 버전 정보**
Linux CentOS7 환경에서 개발되었으며, 알티베이스 설치가 가능한 환경에서 이용 가능합니다.
* Python - 3.6.12
* Django - 3.2.9
* Jpype - 1.3.0
* JayDeBeApi - 1.2.3
### Dashboard 제작을 위한 오픈소스 버전 정보
* telegraf - 1.2.0
* influxdb - 1.8.10
* grafana - 6.4.4-1
* odbc - 2.3.2
## Standard BMT(벤치마크 테스트) Guide
서버 2개가 필요하며 서버 1에 테스트할 알티베이스 버전을 설치, 서버 2에는 서버 1에서의 테스트 결과를 저장하고 웹서버로 사용합니다.
알티베이스 버전별 설치파일 및 매뉴얼은 Altibase 고객지원서비스 포털 ( http://support.altibase.com/ )에서 확인 및 다운로드가 가능합니다.
서버 1에는 테스트를 위해 테스트를 자동으로 수행할 수 있도록 standard_BMT/server1/sys_home/performance 폴더를 서버 1의 시스템 홈 디렉토리에 저장 후 아래 명령을 통해 실행 권한을 부여합니다.
```
chmod -R 755 performance
```
standard_BMT/altibase_home폴더에 있는 bin폴더 안의 파일들을 알티베이스 설치 디렉토리의 bin 폴더 안에 넣고, lib폴더 안의 파일도 알티베이스 설치 디렉토리의 lib 폴더에 넣어줍니다.
이때 bin/qamsperf와 lib/qamsconnector.jar에 아래 명령을 통해 실행 권한을 부여합니다.
```
chmod 777 qamsperf
chmod 777 qamsconnector.jar
```
이후 qamsperf 명령어를 실행하기 위해 /bin/bash를 아래 명령어를 통해 소프트링크를 생성해줍니다.(sudo 권한 필요)
```
ln -s /bin/bash /usr/local/bin/bash
```
서버 2에는 서버 1에서 받을 데이터 저장을 위해 standard_BMT/server2/sys_home/creatTable.sql을 시스템 홈 디렉토리에 저장 후 다음 명령어를 실행하여 Table, Column 정보를 생성합니다.
```
is -f creatTable.sql
```
서버 1, 2 환경 설정이 완료되었다면 서버 1, 2에 알티베이스 서버가 작동 중인지 확인 후 아래 명령어를 통해 테스트를 수행합니다.
이때, 서버1의 메모리 용량이 작다면 scale 조절을 통해 낮은 값으로 테스트를 진행합니다.(scale = 1 기준 메모리 64GB 권장)
server2-ip 자리에 서버2의 ip를 넣어주고, 알티베이스 설치시에 포트를 변경했다면 변경된 포트 정보로 변경합니다.
```
qamsperf --item=s05-1 --times=5 --scale=1 --noperf --db_name={server2-ip}:20300/mydb
```
테스트 완료 후 다른 버전으로 변경하여 다시 테스트를 진행할 경우 $HOME/.bash_profile의 ALTIBASE_ENV를 알맞게 변경하고 아래 명령어를 실행합니다.
```
source ~/.bash_profile
```
