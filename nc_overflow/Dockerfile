FROM debian:bullseye-slim

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get -y install build-essential
RUN apt-get install -y g++ xinetd
ENV TERM=linux

# 사용자 정보 추가
RUN useradd -m attack
# 작업 디렉토리 설정 
WORKDIR /home/attack


COPY overflow.cpp /home/attack/
RUN g++ -o overflow overflow.cpp -pthread
COPY attack /etc/xinetd.d/attack

RUN chown -R root:root /home/attack
RUN chown root:attack /home/attack/overflow


RUN chmod 755 /home/attack
RUN chmod 755 /home/attack/overflow
RUN chmod +x /home/attack/overflow

WORKDIR /home/attack


RUN echo "attack 5001/tcp" >> /etc/services

CMD ["/usr/sbin/xinetd","-dontfork"]