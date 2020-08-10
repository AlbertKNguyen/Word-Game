FROM mike314/boost_cpp:1.0.1

WORKDIR /opt/crowapp

COPY . .

RUN make

EXPOSE 18080

CMD [ "make", "run" ]
