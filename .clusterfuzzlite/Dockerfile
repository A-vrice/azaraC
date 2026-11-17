# base-builder は OSS-Fuzz 公式のローリングイメージで、タグ付けが前提でないため DL3006 を抑止する。
# hadolint ignore=DL3006
FROM gcr.io/oss-fuzz-base/base-builder
COPY . $SRC/azaraC
WORKDIR $SRC/azaraC
COPY ./.clusterfuzzlite/build.sh $SRC/
