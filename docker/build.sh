#!/usr/bin/env bash
# assume have checked out into the repo
set -ex

if [ -z ${GITHUB_TOKEN+x} ]; then
  if [ -z ${1+x} ]; then
    echo "GITHUB_TOKEN not present, the first argument should be the token"
    exit 1
  fi
  GITHUB_TOKEN=$1
fi

git config --global user.name "Brian Li [AUTO]"
git config --global user.email brianlee0415@gmail.com

cd codebook

if [ -f codebook.pdf ]; then
    rm codebook.pdf
fi

xelatex codebook.tex && xelatex codebook.tex && xelatex codebook.tex

curtime=$(date +"%Y-%m-%d_%H:%M:%S")

echo "Current time is: $curtime."

git clone https://oauth2:$GITHUB_TOKEN@github.com/BrianLii/hj84.git \
    --branch codebook --single-branch artifacts
cp codebook.pdf artifacts/codebook.pdf

cd artifacts
git add codebook.pdf
git commit -m "Auto build, $curtime"
git push origin codebook

echo "Build Done."
