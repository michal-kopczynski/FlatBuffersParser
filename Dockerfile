# fb-parser-build-env
FROM acgetchell/vcpkg-image as fb-parser-build-env

RUN vcpkg install restinio


# fb-parser-build-dev
FROM fb-parser-build-env as fb-parser-build

COPY / /src

RUN cd /src \
  && rm -rf build \
  && mkdir build \
  && cd build \
  && cmake .. -DBUILD_TESTING=ON -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
  && make


# fb-parser-tests-unit
FROM fb-parser-build as fb-parser-tests-unit

RUN cd /src/build \
  && make test


# fb-parser-deploy
FROM ubuntu:20.04 as fb-parser-deploy

RUN apt update -y

COPY --from=fb-parser-build /src/bin/FlatBuffersParser /usr/bin/FlatBuffersParser

ENTRYPOINT [ "FlatBuffersParser" ] 


# fb-parser-tests-api
FROM python:3.7.1 as fb-parser-tests-api

COPY /tests/api /tests

WORKDIR /tests
RUN pip install -r requirements.txt

ENTRYPOINT [ "pytest", ".", "-s" ] 
