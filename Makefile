all: reiniciar_router

reiniciar_router: reiniciar_router.c
	cc reiniciar_router.c -lcurl -o reiniciar_router
