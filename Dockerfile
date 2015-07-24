# This machine spec builds on top of reba, an open source "renderer base".
#
# For more information on reba, see its README at:
#     https://github.com/prideout/reba
#

FROM prideout/reba
EXPOSE 8082
RUN pip install pytest
RUN pip install bottle
RUN echo "cd /island" >> /root/.bashrc
