#include "multiTDC.h"

multiTDC::multiTDC(int ntdc, int *TDC_channel_import, float *TDC_value_import)
{
  TDChits = 0;
  int *ChannelCounter = new int[896];
  int *GoodChannelCounter = new int[896];
  
  //   printf("L7\n");
  for(int i=0;i<896;i++){ChannelCounter[i]=0;}
  for(int i=0;i<896;i++){GoodChannelCounter[i]=0;}
  for(int n=0;n<ntdc;n++)
  {
    if(TDC_channel_import[n]>0 && TDC_channel_import[n]<7*128)ChannelCounter[TDC_channel_import[n]]+=1;
    if(TDC_channel_import[n]>0 && TDC_channel_import[n]<7*128 && TDC_value_import[n]>PulseLimits[0] && TDC_value_import[n]<PulseLimits[1])GoodChannelCounter[TDC_channel_import[n]]+=1;
  }
  //   printf("L14\n");
  for(int n=0;n<ntdc;n++)//Loop over and dispose of the simple events (the single hit events)
  {
    //   printf("L18\n");
    if(TDC_channel_import[n]>=6*128+48 && TDC_channel_import[n]<7*128)
    {
      if(ChannelCounter[TDC_channel_import[n]]==0)
      {
	printf("Something has gone wrong - the number of counts for channel %d is expected to be zero but something is seen.\n",TDC_channel_import[n]);
	
      }
      else if(ChannelCounter[TDC_channel_import[n]]==1)//Only store events from the last TDC -> These are the ancillary detector events
    {
      //The reason that we do this this way is to look at how many events fall outside the good beampulse - only when we have multiple hits do we need to worry about the multiple hits and this should be quicker 
      SetChannel(TDC_channel_import[n]);
      SetValue(TDC_value_import[n]);
      TDChits++;
    }
//     else if(ChannelCounter[TDC_channel_import[n]]>1)
//     {
//       //How do we do this? The easiest thing is probably to do something like store which tdc input events correspond to the multiple hits in the same channel and then to work out which one we would prefer to accept based on where it falls within the event
// //       printf("More than one TDC hit found in channel %d\n",TDC_channel_import[n]);
//     
// 
//     }
    }
  }
  SetHits(TDChits);
  delete ChannelCounter;
  delete GoodChannelCounter;
}

multiTDC::~multiTDC()
{
}

void multiTDC::PrintEvent()
{
  printf("Size of event: %d\n", SizeOfEvent());
  TDCchannels.clear();
  TDCvalues.clear();
}

bool multiTDC::TestEvent()
{
  bool result = true;
  if(TDChits != TDCchannels.size()){printf("TDChits != TDCchannels.size()\n");result = false;}
  if(TDChits != TDCvalues.size()){printf("TDChits != TDCvalues.size()\n");result = false;}
  if(TDCchannels.size() != TDCvalues.size()){printf("TDCchannels.size() != TDCvalues.size()\n");result = false;}
  return result;
}

void multiTDC::ClearEvent()
{
  TDChits=0;
  TDCchannels.clear();
  TDCvalues.clear();
}

unsigned int multiTDC::SizeOfEvent()
{
  return TDChits;
}