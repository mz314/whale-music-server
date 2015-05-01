#include <alsa/asoundlib.h>
#include <stdio.h>


void checkerr(int err)
{
 if (err<0)
 {printf("%s",snd_strerror(err));
  exit(0);}
}

 
 


void noise(snd_pcm_t *alsa)
{
 int i;
 int err;
 char buff[128];
 
}



 

 
 


int main()
{
 void *buff=0;
 int err,i,frames=32;
 unsigned int size;
 FILE *f;
 snd_pcm_hw_params_t *hw_params;
 snd_pcm_t *playback;
 err=snd_pcm_open(&playback,"plug:dmix",SND_PCM_STREAM_PLAYBACK,SND_PCM_ASYNC);
 checkerr(err);
 err=snd_pcm_hw_params_malloc(&hw_params);
 checkerr(err);
 err=snd_pcm_hw_params_any(playback,hw_params);
 checkerr(err);
 err = snd_pcm_hw_params_set_access (playback, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
 checkerr(err);
 err=snd_pcm_hw_params_set_rate_resample(playback, hw_params,1);
 checkerr(err);
 err=snd_pcm_hw_params_set_format (playback, hw_params, SND_PCM_FORMAT_S16_LE);
 checkerr(err);
 err = snd_pcm_hw_params_set_rate (playback, hw_params, 44100, 0);
 checkerr(err);
 err = snd_pcm_hw_params_set_channels (playback, hw_params, 2);
 checkerr(err);
 err=snd_pcm_hw_params_set_periods_near(playback,hw_params,&frames,0);
 checkerr(err);
 err = snd_pcm_hw_params (playback, hw_params);
 checkerr(err);
 snd_pcm_hw_params_free (hw_params);
 printf("ALSA test!\n");
 err=snd_pcm_prepare(playback);
 checkerr(err);
 printf("OPENING WAV...\n");
 f=fopen("/home/maciek/test.wav","rb");
 if (f==0)
   exit(0);
 fseek(f,0x04,SEEK_SET);
 fread(&size,4,1,f);
 printf("Allocation %u bytes..\n.",size);
 buff=malloc(size);
 fseek(f,0x08,SEEK_SET);
 fread(buff,size,1,f);
 fclose(f);
 if (buff==0)
  printf("ERR\n");
 printf("Playing %u bs.\n",size);
  for (i=0; i<10000; i++) 
    err = snd_pcm_writei (playback, buff, size);
  if (err!=size)
    checkerr(err);
 
 snd_pcm_close(playback);
 return 0;
}