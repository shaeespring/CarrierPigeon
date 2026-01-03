FROM ubuntu:24.04

COPY backend .

RUN apt-get update
RUN apt-get install build-essential

WORKDIR ./backend/

RUN make all

WORKDIR ./

CMD ["sh"]
