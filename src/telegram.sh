#!/bin/bash

TELEGRAM_BOT_TOKEN="5480276497:AAGEVDL4qn34UTFHQlRD4v9Xa6-23XOkx-k"
TELEGRAM_USER_ID=234044535
TIME="10"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

TEXT="Deploy status: $CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0AStage:+"$CI_JOB_STAGE"%0ABranch:+$CI_COMMIT_REF_SLUG"

if [ $CI_JOB_STATUS == failed ]; then
	curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL 
elif [[ $CI_JOB_STATUS == success ]] && [[ $CI_JOB_STAGE == test ]]; then
	curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL 
elif [ $CI_JOB_STAGE == deploy ]; then
	curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL 
fi
