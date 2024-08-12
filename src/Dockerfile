ARG DLESS_TAG=latest

FROM gcc:6 AS build-env
#FROM gcr.io/distroless/base-nossl as build-env
COPY . /app
WORKDIR /app
RUN make

#FROM gcr.io/distroless/base-nossl:debug
#FROM gcr.io/distroless/base:debug

FROM gcr.io/distroless/cc

COPY --from=build-env /app/msc /app/
WORKDIR /app
CMD ["./msc]
